#include <iostream>
#include <vector>
class Tag {
protected:
    friend class Parser;
    unsigned int id;
    std::string name;
    bool type=0;
    std::vector<std::pair<std::string, std::string>> attrs;
public:
    void pushAttr(std::pair<std::string, std::string> attrArg) {
        attrs.insert(std::lower_bound(attrs.begin(), attrs.end(), attrArg), attrArg);
    }
    void printAttrs() {
        std::cout << name << "(ID " << id << ")" << std::endl << "--------------------\n";
        for(auto i:attrs) {
            std::cout << i.first << ": " << i.second << std::endl;
        }
        std::cout << "--------------------\n";
    }
};
class Parser {
protected:
    static unsigned int tagsAm;
    std::vector<Tag> tags;
public:
    void addTag(std::string tagStr) {
        Tag tag;
        try {
        tag.id = tagsAm;
        (tagStr.substr(0,2)=="</" && tagStr[tagStr.size()-1]=='>')?tag.type=0:(tagStr[0]=='<' && tagStr[tagStr.size()-1]=='>')?tag.type=1,tagsAm++:throw 1;
        if(tag.type) {
        std::pair<std::string, std::string> attr;
        bool phase=0;
        for(signed int i=1, c=0;i<tagStr.size();((tagStr[i]=='='||tagStr[i]=='\"') && c<2)?c++,i++:(tagStr[i]=='\"')?c=0,tag.pushAttr(attr),attr={},i++:i++) {
            if(!phase)tag.name+=(tagStr[i] == ' ' || tagStr[i] == '>')?'\0',phase++:tagStr[i];
            else {
                if(!c && tagStr[i]!=' ' && tagStr[i]!='=')attr.first+=tagStr[i];
                else if(c==2 && tagStr[i] != '\"' && tagStr[i]!='=') attr.second+=tagStr[i];
            }
        }
        }
        }
        catch(int e) {
            std::cout << "Error " << e;
            (e==1)?std::cout << ": wrong constructor statement for tag with tagId " << tag.id : std::cout << "Unknown error\n";
        }
    }
};
unsigned int Parser::tagsAm = 0;
int main() {
    unsigned int n;
    Parser parser;
    parser.addTag("<tag-1 value = \"some value\" type=\"someType\">");
    parser.addTag("<tag-2 Sentence=\"A random sentence.\">");
    /*
    to do:
    program closing tag, tags vector, tag query with binary search, nested tags
    */
    return 0;
}
