#include <iostream>
#include <vector>
class Tag {
protected:
    friend class Parser;
    unsigned int id;
    std::string name;
    bool type=0;
};
class OpenTag : public Tag {
protected:
    std::vector<std::pair<std::string, std::string>> attrs;
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
        bool phase=0;
        for(signed int i=1;i<tagStr.size();i++) {
            if(!phase)tag.name+=(tagStr[i] == ' ' || tagStr[i] == '>')?phase=1:tagStr[i];
            else {

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
    Parser parser;
    parser.addTag("<tag-1 value = \"some value\" type=\"someType\">");
    return 0;
}
