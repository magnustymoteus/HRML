#include <iostream>
#include <vector>

class Tag {
protected:
    friend class Parser;
    unsigned int id;
    std::string name;
    std::vector<std::pair<std::string, std::string>> attrs;
    std::vector<Tag> children;
public:
    signed int getAttr(const std::string keyStrArg) {
        signed int l=0, r=attrs.size()-1, p;
        while(l<=r) {
            p=(l+r)/2;
            if(attrs[p].first == keyStrArg) return p;
            (keyStrArg>attrs[p].first)?l=p+1:r=p-1;
        }
        return -1;
    }
    void insertAttr(const std::pair<std::string, std::string> &attrRef) {
        attrs.insert(std::lower_bound(attrs.begin(), attrs.end(), attrRef), attrRef);
    }
    void outputInfo() {
        std::cout << name << "(ID " << id << ")" << std::endl << "--------------------\n";
        for(auto i:attrs) {
            std::cout << i.first << ": " << i.second << std::endl;
        }
        std::cout << "--------------------\n\n";
    }
};
class Parser {
protected:
    static unsigned int tagsAmount;
    std::vector<Tag> tags;
    std::vector<Tag> tagLayers;
    signed int currTagIndex = -1;

    signed int bSearchTag(const std::string &tagNameRef, bool opt) {
        signed int l=0,r=tags.size()-1,p;
        while(l<=r) {
            p=(l+r)/2;
            if((tags[p].name==tagNameRef && !opt)) return p;
            (tagNameRef>tags[p].name)?l=p+1:r=p-1;
        }
        return (!opt)?-1:r+1;
    }
public:
    void printTags() {
        for(auto tag : tags) {
            std::cout << "'" << tag.name << "' ";
        }
    }
    void printChildrenOf(std::string tagNameArg) {
        Tag tag = tags[bSearchTag(tagNameArg, 0)];
        for(auto childTag : tag.children) {
            std::cout << childTag.name << " ";
        }
    }
    void insertTag(const Tag &tagRef) {
        if(tagLayers.size()) tags[bSearchTag(tagLayers[tagLayers.size()-1].name,0)].children.push_back(tagRef);
        tagLayers.push_back(tagRef);
        tags.insert(tags.begin()+bSearchTag(tagRef.name, 1), tagRef);
    }
    void closeTag() {
        tagLayers.pop_back();
    }
    void addTag(const std::string tagStr) {
        try {
        bool type=0;
        unsigned int id;
        (tagStr.substr(0,2)=="</" && tagStr[tagStr.size()-1]=='>')?type=0:(tagStr[0]=='<' && tagStr[tagStr.size()-1]=='>')?type=1:throw 1;
        tagsAmount++;
        if(type) {
        Tag tag;
        tag.id = tagsAmount;
        std::pair<std::string, std::string> attr;
        bool phase=0;
        for(signed int i=1, c=0;i<tagStr.size();((tagStr[i]=='='||tagStr[i]=='\"') && c<2)?c++,i++:(tagStr[i]=='\"')?c=0,tag.insertAttr(attr),attr={},i++:i++) {
            if(!phase) {
                if(tagStr[i] != ' ' && tagStr[i] != '>') tag.name+=tagStr[i];
                else phase=1;
            }
            else {
                if(!c && tagStr[i]!=' ' && tagStr[i]!='=')attr.first+=tagStr[i];
                else if(c==2 && tagStr[i] != '\"' && tagStr[i]!='=') attr.second+=tagStr[i];
                }
            }
            insertTag(tag);
        }
        else {
            closeTag();
            }
        }

        catch(int e) {
            std::cout << "Error " << e;
            (e==1)?std::cout << ": wrong constructor or closing statement for tag with tagId " << tagsAmount : std::cout << "Unknown error\n";
        }
    }
};
unsigned int Parser::tagsAmount = 0;
int main() {
    Parser parser;
    parser.addTag("<tag-1 value = \"some value\" type=\"someType\">");
    parser.addTag("<tag-2 Sentence=\"A random sentence.\">");
    parser.addTag("</tag-2>");
    parser.addTag("<tag-3 ab = \"a\" bc=\"c\" ba = \"b\">");
    parser.addTag("</tag-3>");
    parser.addTag("</tag-1>");
    /*
    to do:
    opening and closing tag same id, tag query system, clean and shorten unnecessary code
    */
    return 0;
}
