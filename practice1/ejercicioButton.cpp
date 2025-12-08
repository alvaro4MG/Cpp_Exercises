#include <iostream>
#include <vector>
#include <string>

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
        ~Button(){}

        void press(){
            isPressed = true;
        }
        void release(){
            isPressed = false;
        }

        void display() const{
            if(isPressed){
                cout << "Button " << label << " is pressed"  << endl;
            }else{
                cout << "Button " << label << " is released"  << endl;
            }
        }

};

int main(){
    vector<Button> botones;

    botones.push_back(Button("boton1"));
    botones.push_back(Button("boton2"));
    botones.push_back(Button("boton3"));

    botones[0].press();

    for(const auto& b : botones){
        b.display();
    }

    return 0;
}