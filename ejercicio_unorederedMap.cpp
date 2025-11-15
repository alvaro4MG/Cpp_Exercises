#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;


class Button {
    private: 
        string label;

    public:
        Button(const string& label){
            this->label = label;
        }
        
        string getLabel() const{
            return label;
        }

        void press(){}


};


int main(){

    // Sin pointer
    unordered_map<string, Button> botones;

    botones.insert({"Play", Button("Play")});
    botones.insert({"Options", Button("Options")});
    botones.insert({"Exit", Button("Exit")});

    botones["Play"].press();

    // Con pointer
    unordered_map<string, unique_ptr<Button>> botones_ptr;

    botones["Play"] = make_unique<Button>("Play");
    // botones.insert({"Play", make_unique<Button>("Play")});
    botones["Options"] = make_unique<Button>("Options");
    botones["Exit"] = make_unique<Button>("Exit");

    botones["Play"].press();

    return 0;
}