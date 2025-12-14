#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string KPRODUCTS="products.bin";
const string KTYPES="types.bin";
const int KREF=16;
const int KNAME=50;
const int KDESC=200;

// To read from "products.bin"
struct Product{
  char ref[KREF];
  char name[KNAME];
  char desc[KDESC];
  unsigned code;
  float price;
  bool novel;
  int units;
};

// To read from "types.bin"
struct Type{
  unsigned code;
  char desc[KDESC];
};

bool checkArguments(int argc,char *argv,string &fileName,string &separator){

}

string getDescription(unsigned code,vector<Types> vectorTypes){
  string description;
  bool found=false;
  
  for(int i=0;i<vectorTypes.size() && !found;i++){
    if(vectorTypes[i].code==code){
      description=vectorTypes[i].description;
      found=true;
    }
  }
  
  return description;
}

int main(int argc,char *argv[]){
  ifstream fileProducts;
  ifstream fileTypes;
  ofstream fileOutput;
  string fileName;
  string separator;
  vector<Type> vectorTypes;

  if(checkArguments(argc,argv,fileName,separator)){
    fileProducts.open(KPRODUCTS,ios::in|ios::binary);
    if(fileProducts.is_open()){
      fileTypes.open(KTYPES,ios::in|ios::binary);
      if(fileTypes.is_open()){
        fileOutput.open(fileName,ios::out);
        if(fileOutput.is_open()){
          // Store in a vector all the types and its descriptions
          Type newType;
          while(fileTypes.read((char *)&newType,sizeof(newType))){
            vectorTypes.push_back(newType);
          }
        
          Product newProduct;
          string temp;
          
          while(fileProduct.read((char *)&newProduct,sizeof(newProduct))){
            fileOutput << newProduct.ref << separator;
            
            temp=newProduct.name;
            if(temp.find(" ")!=string::npos){
              fileOutput << "\"" << newProduct.name << "\"" << separator;
            }
            else{
              fileOutput << newProduct.name << separator;
            }

            temp=newProduct.desc;
            if(temp.find(" ")!=string::npos){
              fileOutput << "\"" << temp.substr(100) << "\"" << separator;
            }
            else{
              fileOutput << temp.substr(100) << separator;
            }
            
            fileOutput << getDescription(newProduct.code,vectorTypes) << separator
                       << newProduct.price << separator;
            
            if(!newProduct.novel && newProduct.units>100){
              fileOutput << 100 << endl;
            }
            else{
              fileOutput << newProducts.units << endl;        
            }
          }
        
          fileOutput.close();
        }
        else{
          cout << "ERROR: cannot open " << fileName << endl;
        }
      
        fileTypes.close();
      }
      else{
        cout << "ERROR: cannot open " << KTYPES << endl;
      }
  
      fileProducts.close();
    }
    else{
      cout << "ERROR: cannot open " << KPRODUCTS << endl;
    }
  }
  else{
    cout << "Use: " << argv[0] << " -f <file_name> -s <separator> [-v]" << endl;
  }
  
}