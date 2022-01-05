#include <iostream>
#include <vector>

class Tag {
protected:
    friend class Parser;
    unsigned int id;
    std::string name;
    bool closed=0;
    std::vector<std::pair<std::string, std::string>> attrs;
    std::vector<Tag> children;
public:
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
public:
    void closeTag(const std::string &tagNameRef) {
        //to do
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
            if(!phase)tag.name+=(tagStr[i] == ' ' || tagStr[i] == '>')?'\0',phase++:tagStr[i];
            else {
                if(!c && tagStr[i]!=' ' && tagStr[i]!='=')attr.first+=tagStr[i];
                else if(c==2 && tagStr[i] != '\"' && tagStr[i]!='=') attr.second+=tagStr[i];
                }
            }
            tags.push_back(tag); //change to insert (binary search)
        }
        else {
            std::string name;
            for(unsigned int i=1;i<tagStr.size();i++) {
                if(tagStr[i] == ' ' || tagStr[i] == '>')name+=tagStr[i];
            }
            closeTag(name);
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
    unsigned int n;
    Parser parser;
    parser.addTag("<tag-1 value = \"some value\" type=\"someType\">");
    parser.addTag("</tag-1>");
    parser.addTag("<tag-2 Sentence=\"A random sentence.\">");
    /*
    to do:
    program closing tag, opening and closing tag same id, tags vector, tag query with binary search, children tags, nested tags
    */
    return 0;
}
