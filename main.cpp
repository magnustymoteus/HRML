#include <iostream>
#include <vector>
#include <memory>
class Tag {
public:
    friend class Parser;
    unsigned int id;
    std::string name;
    std::vector<std::pair<std::string, std::string>> attrs;
    std::vector<std::shared_ptr<Tag>> children;
    std::shared_ptr<Tag> parentTagPtr;
    Tag(std::string nameArg) : name(nameArg) {}
    Tag() {}
public:
    signed int getAttr(const std::string &keyStrArg) {
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
public:
    static unsigned int tagsAmount;
    std::vector<std::shared_ptr<Tag>> tags;
    std::vector<std::shared_ptr<Tag>> tagLayerPtrs;
public:
     signed int bSearchTag(std::vector<std::shared_ptr<Tag>> tagVectorRef, const std::string &tagNameRef, bool opt) {
        signed int l=0,r=tagVectorRef.size()-1,p;
        while(l<=r) {
            p=(l+r)/2;
            if((tagVectorRef[p]->name==tagNameRef && !opt)) return p;
            (tagNameRef>tagVectorRef[p]->name)?l=p+1:r=p-1;
        }
        return (!opt)?-1:r+1;
    }
    void printLayers() {
        std::cout << "\nLAYERS:\n--------------\n";
        for(auto tag : tagLayerPtrs) {
            std::cout << tag->name << ' ' << tag.get() << std::endl;
        }
        std::cout << "--------------\n\n";
    }
    void printAllTags() {
        std::cout << "\nTAGS:\n--------------\n";
        for(auto tag : tags) {
            std::cout << tag->name << std::endl;
            for(auto tagChild : tag->children) {
                std::cout << "CHILDREN:" << tagChild->name << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << "--------------\n\n";
    }
    void initializeInput() {
        std::string inputStr, queryStr;
        signed int inputsNum, queriesNum;
        std::cin >> inputsNum >> queriesNum;
        std::cin.ignore();
        while(inputsNum--) {std::getline(std::cin, inputStr); addTag(inputStr);}
        while(queriesNum--) {std::getline(std::cin, queryStr); std::cout << query(queryStr) << std::endl;}
    }
    std::string query(const std::string queryStrArg) {
        std::shared_ptr<Tag> currTag(new Tag);
        std::string str;
        char op;
        for(signed int i=0;i<queryStrArg.size();i++) {
            if(queryStrArg[i]!='.' && queryStrArg[i]!='~') str+=queryStrArg[i];
            else {
                if(!op) {
                    signed int resNum = bSearchTag(tags, str, 0);
                    if(resNum==-1) return "Not Found!";
                    currTag = tags[resNum];
                }
                else if(op=='.') {
                    signed int resNum = bSearchTag(currTag->children, str, 0);
                    if(resNum==-1) return "Not Found!";
                    currTag = currTag->children[resNum];
                }
                str.clear();
                op = queryStrArg[i];
            }
        }
            signed int resNum = currTag->getAttr(str);
            return (resNum==-1)? "Not Found!" : currTag->attrs[resNum].second;
        }
    void insertTag(std::shared_ptr<Tag> tagRef) {
        if(tagLayerPtrs.size()) {
            tagRef->parentTagPtr = tagLayerPtrs[tagLayerPtrs.size()-1];
            tagRef->parentTagPtr->children.insert(tagRef->parentTagPtr->children.begin()+bSearchTag(tagRef->parentTagPtr->children, tagRef->name, 1), tagRef);
        }
        else tags.insert(tags.begin()+bSearchTag(tags, tagRef->name, 1), tagRef);
        tagLayerPtrs.push_back(tagRef);
    }
    void closeTag() {
        tagLayerPtrs.pop_back();
    }
    void addTag(const std::string tagStr) {
        try {
        bool type=0;
        unsigned int id;
        (tagStr.substr(0,2)=="</" && tagStr[tagStr.size()-1]=='>')?type=0:(tagStr[0]=='<' && tagStr[tagStr.size()-1]=='>')?type=1:throw 1;
        if(type) {
        std::shared_ptr<Tag> tag(new Tag);
        tag->id = tagsAmount++;
        std::pair<std::string, std::string> attr;
        bool phase=0;
        for(signed int i=1, c=0;i<tagStr.size();((tagStr[i]=='='||tagStr[i]=='\"') && c<2)?c++,i++:(tagStr[i]=='\"')?c=0,tag->insertAttr(attr),attr={},i++:i++) {
            if(!phase) {
                if(tagStr[i] != ' ' && tagStr[i] != '>') tag->name+=tagStr[i];
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
   parser.initializeInput();
    /*
    to do:
    clean and shorten unnecessary code
    */
    return 0;
}
