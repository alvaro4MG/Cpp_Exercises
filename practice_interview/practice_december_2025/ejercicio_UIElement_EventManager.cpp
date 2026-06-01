#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

enum class EventType{
    Click,
    Hover
};

class UIElement {
    private: 
        string label;

    public:
        UIElement(const string& label){
            this->label = label;
        }
        ~UIElement(){}

        void onEvent(EventType e){

            cout << "Button " << label << " received ";

            switch(e){
                case EventType::Click:
                    cout << "Click";
                    break;
                case EventType::Hover:
                    cout << "Hover";
                    break;
            }
            
            cout << endl;
        }

};

class EventManager_unique{     //con unique_ptr
    private:
        vector<unique_ptr<UIElement>> elements;
    
    public:
        EventManager(){}

        void addElement(unique_ptr<UIElement> e){
            elements.push_back(move(e));    // move(e) transfiere la propiedad del unique_ptr al vector, evitando fugas de memoria
        }

        void sendEvent(EventType e){
            for(const auto& elem : elements){
                elem->onEvent(e);
            }
        }
};

class EventManager_pointer{
    private:
        vector<UIElement*> elements;
    
    public:
        ~EventManager_pointer(){
            for(auto e : elements){
                delete e;       // Liberamos manualmente la memoria
            }
        }

        void addElement(UIElement* e){
            elements.push_back(e);
        }

        void sendEvent(EventType e){
            for(auto elem : elements){
                elem->onEvent(e);
            }
        }
};

int main(){
    /*vector<unique_ptr<UIElement>> elements;

    elements.push_back(make_unique<UIElement>("evento1"));
    elements.push_back(make_unique<UIElement>("evento2"));
    elements.push_back(make_unique<UIElement>("evento3"));

    for(const auto& e : elements){
        e->onEvent(EventType.Click);
    }*/

    EventManager manager;

    manager.addElement(make_unique<UIElement>("evento1"));
    manager.addElement(make_unique<UIElement>("evento2"));
    manager.addElement(make_unique<UIElement>("evento3"));

    manager.sendEvent(EventType::Click);

    EventManager_pointer man_ptr;

    man_ptr.addElement(new UIElement("evento1"));
    man_ptr.addElement(new UIElement("evento2"));
    man_ptr.addElement(new UIElement("evento3"));

    man_ptr.sendEvent(EventType::Click);

    return 0;
}