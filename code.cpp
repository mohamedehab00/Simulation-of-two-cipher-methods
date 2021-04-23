#include <bits/stdc++.h>
using namespace std;

const int English_Letters_no = 26;
const int Start_Capital_Letters = 65;
const int N = sqrt(English_Letters_no);
char Matrix[5][5];
char Pairs[English_Letters_no/2][2];

//This function takes a letter and encrypt it
char encrypt_letter(char letter , int shift){
    char encrypted_letter;
    int index = toupper(letter) - Start_Capital_Letters;
    int EncryptedIndex = (index+shift) % English_Letters_no;
    encrypted_letter = Start_Capital_Letters + EncryptedIndex;
    return encrypted_letter;
}
//This function takes a letter and decrypt it
char decrypt_letter(char letter , int shift){
    char decrypted_letter;
    int index = toupper(letter) - Start_Capital_Letters;
    int DecryptedIndex = (index - shift + English_Letters_no) % English_Letters_no;
    decrypted_letter = Start_Capital_Letters + DecryptedIndex;
    return decrypted_letter;
}
//This function is the main encrypt function
string CaesarCipherEncrypt(string plainText,int shift){
    string EncryptedMessage = "";
    for(int i = 0 ; i < plainText.length() ; i++){
        if( isspace(plainText[i]) || isdigit(plainText[i]) ){
            EncryptedMessage += plainText[i];
        }
        else if(islower(plainText[i])){
            EncryptedMessage += tolower(encrypt_letter(plainText[i],shift));
        }
        else{
            EncryptedMessage += encrypt_letter(plainText[i],shift);
        }
    }
    return EncryptedMessage;
}
//This function is the main decrypt function
string CaesarCipherDecrypt(string plainText,int shift){
    string DecryptedMessage = "";
    for(int i = 0 ; i < plainText.length() ; i++){
        if( isspace(plainText[i]) || isdigit(plainText[i]) ){
            DecryptedMessage += plainText[i];
        }
        else if(islower(plainText[i])){
            DecryptedMessage += tolower(decrypt_letter(plainText[i],shift));
        }
        else{
            DecryptedMessage += decrypt_letter(plainText[i],shift);
        }
    }
    return DecryptedMessage;
}
//This function checks the presence of a character in a word
bool check_letter(char l , string Keyword){
    for(int i = 0 ; i < Keyword.length() ;i++){
        if (Keyword[i] == l){
            return true;
        }
    }
    return false;
}
//This function returns the keyword with unique letters
string uniqueLetters(string Keyword){
    string word = "";
    for(int i = 0 ; i < Keyword.length() ;i++){
        if (check_letter(toupper(Keyword[i]),word)){
           continue;
        }
        else{
            word += toupper(Keyword[i]);
        }
    }
    return word;
}
//This function forms the general Matrix
void matrix(string Keyword){
    string Key = uniqueLetters(Keyword);
    int p = 0,p1=Start_Capital_Letters;
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(p < Key.length()){
                Matrix[i][j] = Key[p++];
            }
            else{
                while(p1<=Start_Capital_Letters+English_Letters_no){
                    char test = p1;
                    if (test == 'J'){
                        p1+=1;
                        continue;
                    }
                    else if(check_letter(test,Key)){
                        p1+=1;
                        continue;
                    }
                    else{
                        Matrix[i][j] = test;
                        p1+=1;
                        break;
                    }
                }
            }
        }
    }
}
//This function convert the text to pairs
int textToPairs(string Text){
    int i = 0;
    int No = 0;
    while(i < Text.length()){
        if(i+1 == Text.length()){
            Pairs[No][0]=Text[i];
            Pairs[No][1]=Text[i];
            i+=1;
        }
        else{
            if(Text[i] != Text[i+1]){
                Pairs[No][0]=Text[i];
                Pairs[No][1]=Text[i+1];
                i+=2;
            }
            else if(Text[i] == Text[i+1]){
                Pairs[No][0]=Text[i];
                Pairs[No][1]='X';
                i+=1;
            }
        }
        No+=1;
    }
    return No;
}
//This function gets the index of a character in the Matrix
void get_index(char l,int &x , int &y){
    for(int row = 0 ; row < N ; row++){
        for(int col = 0 ; col < N ; col++){
            if(Matrix[row][col] == l){
                x=row;
                y=col;
            }
        }
    }
}
//This function gets the main input of the simulation
void main_Input(string &text,int &methodology){
    cout<<"Text : ";
    cin>>text;
    cout<<"Enter The no. of Methodology you want : \n 1- Caesar Cipher 2- PlayFair"<<endl;
    do{
        cout<<"Please Enter The number : ";
        cin>>methodology;
    }while(methodology > 2 || methodology < 0);
}
int sub_Input(){
    int method;
    do{
        cout<<"Enter The Method no. { 1- Encryption 2- Decryption } : ";
        cin>>method;
    }while(method > 2 || method < 0);
    return method;
}
//The main function of Caesar Cipher
void CaesarCipher(string plainText){
    int shift;
    do{
        cout<<"Enter The Shift Key : ";
        cin>>shift;
    }while(shift < 0 || shift > English_Letters_no);

    int Method = sub_Input();

    if (Method == 1){
        cout<<CaesarCipherEncrypt(plainText,shift)<<endl;
    }
    else if(Method == 2){
        cout<<CaesarCipherDecrypt(plainText,shift)<<endl;
    }
}
//This function checks if is only alphabet
bool string_isalpha(string Text){
    for(int i = 0 ; i < Text.length() ; i++){
        if(!isalpha(Text[i])){
            return false;
        }
    }
    return true;
}
//This function is the main encrypt function
string PlayFairEncryption(string Text,int Limit){
    string EncryptedMessage = "";
    if(string_isalpha(Text)){
        for(int i = 0 ; i < Limit ; i++){
            int x1,y1,x2,y2;
            get_index(toupper(Pairs[i][0]),x1,y1);
            get_index(toupper(Pairs[i][1]),x2,y2);
            if (x1 == x2 and y1 == y2 ){
                if (islower(Pairs[i][0])){
                    EncryptedMessage += tolower(Matrix[x1][((y1+1)+N) % N]);
                }
                else{
                    EncryptedMessage += Matrix[x1][((y1+1)+N) % N];
                }
            }
            else if(x1 == x2){
                if (islower(Pairs[i][0])){
                    EncryptedMessage += tolower(Matrix[x1][((y1+1)+N) % N]);
                }
                else{
                    EncryptedMessage += Matrix[x1][((y1+1)+N) % N];
                }
                if (islower(Pairs[i][1])){
                    EncryptedMessage += tolower(Matrix[x2][((y2+1)+N) % N]);
                }
                else{
                    EncryptedMessage += Matrix[x2][((y2+1)+N) % N];
                }
            }

            else if(y1 == y2){
                if (islower(Pairs[i][0])){
                    EncryptedMessage += tolower(Matrix[((x1+1)+N) % N][y1]);
                }
                else{
                    EncryptedMessage += Matrix[((x1+1)+N) % N][y1];
                }
                if (islower(Pairs[i][1])){
                    EncryptedMessage += tolower(Matrix[((x2+1)+N) % N][y2]);
                }
                else{
                    EncryptedMessage += Matrix[((x2+1)+N) % N][y2];
                }
            }
            else{
                if (islower(Pairs[i][0])){
                    EncryptedMessage += tolower(Matrix[x1][y2]);
                }
                else{
                    EncryptedMessage += Matrix[x1][y2];
                }
                if (islower(Pairs[i][1])){
                    EncryptedMessage += tolower(Matrix[x2][y1]);
                }
                else{
                    EncryptedMessage += Matrix[x2][y1];
                }
            }
        }
    }
    else{
        EncryptedMessage += Text;
    }
    return EncryptedMessage;
}
//This function is the main decrypt function
string PlayFairDecryption(string Text,int Limit){
    string DecryptedMessage = "";
    if(string_isalpha(Text)){
        for(int i = 0 ; i < Limit ; i++){
            int x1,y1,x2,y2;
            get_index(toupper(Pairs[i][0]),x1,y1);
            get_index(toupper(Pairs[i][1]),x2,y2);
            if (x1 == x2 and y1 == y2 ){
                if (islower(Pairs[i][0])){
                    DecryptedMessage += tolower(Matrix[x1][((y1-1)+N) % N]);
                }
                else{
                    DecryptedMessage += Matrix[x1][((y1-1)+N) % N];
                }
            }
            else if(x1 == x2){
                if (islower(Pairs[i][0])){
                    DecryptedMessage += tolower(Matrix[x1][((y1-1)+N) % N]);
                }
                else{
                    DecryptedMessage += Matrix[x1][((y1-1)+N) % N];
                }
                if (islower(Pairs[i][1])){
                    DecryptedMessage += tolower(Matrix[x2][((y2-1)+N) % N]);
                }
                else{
                    DecryptedMessage += Matrix[x2][((y2-1)+N) % N];
                }
            }

            else if(y1 == y2){
                if (islower(Pairs[i][0])){
                    DecryptedMessage += tolower(Matrix[((x1-1)+N) % N][y1]);
                }
                else{
                    DecryptedMessage += Matrix[((x1-1)+N) % N][y1];
                }
                if (islower(Pairs[i][1])){
                    DecryptedMessage += tolower(Matrix[((x2-1)+N) % N][y2]);
                }
                else{
                    DecryptedMessage += Matrix[((x2-1)+N) % N][y2];
                }
            }
            else{
                if (islower(Pairs[i][0])){
                    DecryptedMessage += tolower(Matrix[x1][y2]);
                }
                else{
                    DecryptedMessage += Matrix[x1][y2];
                }
                if (islower(Pairs[i][1])){
                    DecryptedMessage += tolower(Matrix[x2][y1]);
                }
                else{
                    DecryptedMessage += Matrix[x2][y1];
                }
            }
        }
    }
    else{
        DecryptedMessage += Text;
    }
    return DecryptedMessage;
}
//The main function of Play Fair
void PlayFair(string plainText){
    string Keyword;
    do{
        cout<<"Enter The Keyword : ";
        cin>>Keyword;
    }while(!string_isalpha(Keyword));

    matrix(Keyword);

    int Limit = textToPairs(plainText);

    int Method = sub_Input();

    if (Method == 1){
        cout<<PlayFairEncryption(plainText,Limit)<<endl;
    }
    else if(Method == 2){
        cout<<PlayFairDecryption(plainText,Limit)<<endl;
    }
}

//The main function
int main() {
    while(true){
        string text;
        int methodology;
        char choice;
        main_Input(text,methodology);
        if (methodology == 1){
            CaesarCipher(text);
        }
        else if (methodology == 2) {
            PlayFair(text);
        }
        cout<<"Want to continue [Yy/Nn] : ";
        cin>>choice;
        if (choice == 'n' || choice == 'N'){
            break;
        }
    }
    return 0;
}
