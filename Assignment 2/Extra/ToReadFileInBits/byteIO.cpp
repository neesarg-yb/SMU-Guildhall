#include<iostream>
#include<fstream>

using namespace std;

// read next integer from file; return cases are same as readNextByte
bool readNextUnsignedInt(unsigned int &number, ifstream &file) {
  if(file.is_open() && file.good()) {
    file.read ((char *) &number, sizeof(number));
    return true;
  } else {
    cout<<"Can't read next integer"<<endl;
    return false;
  }
}

// read next integer from file; return cases are same as readNextByte
void writeNextUnsignedInt(unsigned int &number, ofstream &file) {
  if(file.is_open() && file.good()) {
    file.write ((char *) &number, sizeof(number));
  } else {
    cout<<"Can't read next integer"<<endl;
  }
}

int main() {
  int byte[8] = {1,1,1,0,0,1,0,0};

  // // To write in file
  // ofstream fout("aByte", ios::binary);
  // if(!fout.good()) {
  //   cout<<"ERROR: can not open file to write.."<<endl;
  //   return 1;
  // }
  //
  // char writeByte;
  // for(int i=0; i<8; i++) {
  //   writeByte |= byte[i] << i;  // <char> |= <0 or 1> << <index of bit>
  // }
  // fout.put(writeByte);
  // unsigned int maxI = 4294967278;  // MAX is 4294967295
  // writeNextUnsignedInt(maxI, fout);
  //
  //
  // fout.close();

  // To read from file
  ifstream fin("out.nbz", ios::binary);
  unsigned int byteCount = 0;
  char readByte;

  fin.get(readByte);
  do {

    if(!fin.good()) {
      cout<<"ERROR: can not open file to read.."<<endl;
      return 1;
    }

    byteCount++;
    cout<<"("<<byteCount<<") ";

    cout<<(int)readByte<<" :";
    for(int i=7; i>=0; i--) {
      bool bit = (readByte >> i) & 1 ;
      cout<<bit;
    }
    cout<<endl;

    fin.get(readByte);
  } while(!fin.eof());


  // unsigned int gotI = 0;
  // if (readNextUnsignedInt(gotI, fin)) cout<<"\nunsigned int = "<<gotI<<endl;

  fin.close();

  return 0;
}
