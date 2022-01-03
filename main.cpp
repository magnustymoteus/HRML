#include <iostream>
#include <vector>
class Tag {
protected:
    friend class Interpreter;
    unsigned int id;
    std::string name;
    std::vector<std::pair<std::string, std::string>> attrs;
    bool type;
};
class Interpreter {
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
            if(!f)tag.name+=(tagStr[i] == ' ' || tagStr[i] == '>')?f++:tagStr[i];
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
unsigned int Interpreter::tagsAm = 0;
int main() {
    Interpreter interpreter;
    interpreter.addTag("<tag-1 value=\"something-ekk\" type=\"someType\">");
    return 0;
}
