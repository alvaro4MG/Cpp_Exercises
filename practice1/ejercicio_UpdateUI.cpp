#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;


class Button {
    private: 
        string label;
        bool isPressed;

    public:
        Button(const string& label){
            this->label = label;
            isPressed = false;
        }
        
        void release(){
            isPressed = false;
        }

        void press(){
            isPressed = true;
        }

        void printState(){
            if(isPressed){
                cout << "Button " << label << " is pressed" << endl;
            }else{
                cout << "Button " << label << " is released" << endl;
            }
        }

};

bool processInput(){
    return (rand() % 2);
}

void updateUI(const unordered_map<string, Button>& botones){
    for(const auto& [name, button] : botones){
        button.printState();
    }
}


int main(){
    srand(time(nullptr));

    unordered_map<string, Button> botones;

    botones.insert({"Play", Button("Play")});
    // botones.emplace("Play", "Play");     // Esto construye el propio botón
    botones.insert({"Options", Button("Options")});
    botones.insert({"Exit", Button("Exit")});


    for(int i = 0; i < 5; i++){
        if(processInput()){
            botones["Play"].press();
        }else{
            botones["Play"].release();
        }

        if(processInput()){
            botones["Options"].press();
        }else{
            botones["Options"].release();
        }

        if(processInput()){
            botones["Exit"].press();
        }else{
            botones["Exit"].release();
        }
        
        updateUI(botones);
        cout << "-----" << endl;
    }

    return 0;
}