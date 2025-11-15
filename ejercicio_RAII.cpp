#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Texture {
    private: 
        string filename;

    public:
        Texture(const string& filename){
            this->filename = filename;
        }

        ~Texture(){
            cout << "Texture " << filename << " destroyed";
        }
        
};


int main(){

    Texture tx1 = Texture("Terrain");
    Texture tx2 = Texture("Sky");
    Texture tx3 = Texture("Ball");  // Tras el scope, se eliminarán todas con el destructor

    return 0;
}