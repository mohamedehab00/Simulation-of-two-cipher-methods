English_Letters_no = 26
Start_Capital_Letters = 65
#This function takes a letter and encrypt it
def encrypt_letter(letter,shift):
    index = ord(letter.upper()) - Start_Capital_Letters
    EncryptedIndex = (index+shift) % English_Letters_no
    return chr(Start_Capital_Letters + EncryptedIndex)
#This function takes a letter and decrypt it
def decrypt_letter(letter,shift):
    index = ord(letter.upper()) - Start_Capital_Letters
    DecryptedIndex = (index - shift + English_Letters_no) % English_Letters_no
    return chr(Start_Capital_Letters  +DecryptedIndex)
#This function is the main encrypt function
def CaesarCipherEncrypt(plainText,shift):
    EncryptedMessage=""
    for letter in plainText:
        if letter == ' ' or letter.isnumeric():
            EncryptedMessage += letter
        elif letter.islower():
            EncryptedMessage += encrypt_letter(letter,shift).lower()
        else :
            EncryptedMessage += encrypt_letter(letter,shift)
    return EncryptedMessage
#This function is the main decrypt function
def CaesarCipherDecrypt(plainText,shift):
    DecryptedMessage=""
    for letter in plainText:
        if letter == ' ' or letter.isnumeric():
            DecryptedMessage += letter
        elif letter.islower():
            DecryptedMessage += decrypt_letter(letter,shift).lower()
        else :
            DecryptedMessage += decrypt_letter(letter,shift)
    return DecryptedMessage
#The main function of Caesar Cipher
def CaesarCipher(plainText):
    shift = int(input("Enter The Shift Key : "))
    
    while shift not in range(English_Letters_no+1):
        shift = int(input("Enter The Shift Key : "))
    
    plainText = plainText.split(" ")

    Method = Input()

    if Method == 1:
        EncryptedMessage = ""
        for word in plainText:
            EncryptedMessage += CaesarCipherEncrypt(word,shift) + " "
        print(EncryptedMessage)
    elif Method == 2:

        DecryptedMessage = ""
        for word in plainText:
            DecryptedMessage += CaesarCipherDecrypt(word,shift) + " "
        print(DecryptedMessage)
#This function returns the keyword with unique letters
def unique_letters(Keyword):
    word = []
    for i in range(len(Keyword)):
        if Keyword[i] not in word :
            word.append(Keyword[i])
    return "".join(word)
#This function forms the general Matrix
def matrix(Keyword):
    Letters = [chr(n) for n in range(Start_Capital_Letters,Start_Capital_Letters+English_Letters_no)]
    Matrix = [[],[],[],[],[]]
    Keyword = unique_letters(Keyword)
    for row in range(int(English_Letters_no**0.5)):
        for col in range(int(English_Letters_no**0.5)):
            if Keyword != "":    
                Matrix[row].append(Keyword[0])
                Letters.remove(Keyword[0])
                Keyword = Keyword[1:]
            else:
                if Letters[0] == 'J':
                    Letters = Letters[1:]
                Matrix[row].append(Letters[0])
                Letters = Letters[1:]
    return Matrix
#This function convert the text to pairs
def plainToPairs(plainText):
    pairs = []
    i=0
    while i < len(plainText):
        if i+1 == len(plainText):
            pairs.append([plainText[i],plainText[i]])
            i+=1
        else:
            if plainText[i] != plainText[i+1] :
                pairs.append([plainText[i],plainText[i+1]])
                i+=2
            elif plainText[i] == plainText[i+1]:
                pairs.append([plainText[i],"X"])
                i+=1
    return pairs
#This function gets the index of a character in the Matrix
def get_index(letter,Matrix):
    for row in range(int(English_Letters_no**0.5)):
        for col in range(int(English_Letters_no**0.5)):
            if Matrix[row][col] == letter:
                return row,col
    else:
        return None , None
#This function is the main encrypt function
def PlayFairEncryption(plainText,Matrix):
    EncryptedMessage = ""
    if(plainText.isalpha()):
        pairs = plainToPairs(plainText)
        for i in pairs:
            x1,y1 = get_index(i[0].upper(),Matrix)
            x2,y2 = get_index(i[1].upper(),Matrix)
            
            if x1 == x2 and y1 == y2 :
                if i[0].islower():
                    EncryptedMessage += Matrix[x1][((y1+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)].lower()
                else:
                    EncryptedMessage += Matrix[x1][((y1+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)]
            
            elif x1 == x2 :
                if i[0].islower():
                    EncryptedMessage += Matrix[x1][((y1+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)].lower()
                else:
                    EncryptedMessage += Matrix[x1][((y1+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)]
                if i[1].islower():
                    EncryptedMessage += Matrix[x2][((y2+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)].lower()
                else:
                    EncryptedMessage += Matrix[x2][((y2+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)]
                
            elif y1 == y2 :
                if i[0].islower():
                    EncryptedMessage += Matrix[((x1+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y1].lower()
                else:
                    EncryptedMessage += Matrix[((x1+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y1]
                if i[1].islower():
                    EncryptedMessage += Matrix[((x2+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y2].lower()
                else:
                    EncryptedMessage += Matrix[((x2+1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y2]

            else: 
                if i[0].islower():
                    EncryptedMessage += Matrix[x1][y2].lower()
                else:
                    EncryptedMessage += Matrix[x1][y2]
                if i[1].islower():
                    EncryptedMessage += Matrix[x2][y1].lower()
                else:
                    EncryptedMessage += Matrix[x2][y1]
    else:
        EncryptedMessage += plainText
    return EncryptedMessage
#This function is the main decrypt function
def PlayFairDecryption(plainText,Matrix):
    DecryptedMessage = ""
    if(plainText.isalpha()):
        pairs = plainToPairs(plainText)
        for i in pairs:
            x1,y1 = get_index(i[0].upper(),Matrix)
            x2,y2 = get_index(i[1].upper(),Matrix)
            if x1 == x2 and y1 == y2 :
                if i[0].islower():
                    DecryptedMessage += Matrix[x1][((y1-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)].lower()
                else:
                    DecryptedMessage += Matrix[x1][((y1-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)]
            
            elif x1 == x2:
                if i[0].islower():
                    DecryptedMessage += Matrix[x1][((y1-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)].lower()
                else:
                    DecryptedMessage += Matrix[x1][((y1-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)]
                if i[1].islower():
                    DecryptedMessage += Matrix[x2][((y2-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)].lower()
                else:
                    DecryptedMessage += Matrix[x2][((y2-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)]

            elif y1 == y2:
                if i[0].islower():
                    DecryptedMessage += Matrix[((x1-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y1].lower()
                else:
                    DecryptedMessage += Matrix[((x1-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y1]
                if i[1].islower():
                    DecryptedMessage += Matrix[((x2-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y2].lower()
                else:
                    DecryptedMessage += Matrix[((x2-1)+int(English_Letters_no**0.5)) % int(English_Letters_no**0.5)][y2]

            else: 
                if i[0].islower():
                    DecryptedMessage += Matrix[x1][y2].lower()
                else:
                    DecryptedMessage += Matrix[x1][y2]
                if i[1].islower():
                    DecryptedMessage += Matrix[x2][y1].lower()
                else:
                    DecryptedMessage += Matrix[x2][y1]
    else:
        DecryptedMessage += plainText
        
    return DecryptedMessage
#This function is the main decrypt function
def PlayFair(plainText):
    Keyword = input("Enter The Keyword : ")
    
    while not Keyword.isalpha():
        Keyword = input("Enter The Keyword : ")
    
    plainText = plainText.split(" ")

    Matrix = matrix(Keyword.upper())
    
    Method = Input()

    if Method == 1:
        EncryptedMessage = ""
        for word in plainText:
            EncryptedMessage += PlayFairEncryption(word,Matrix) + " "
        print(EncryptedMessage)
        
    elif Method == 2:
        DecryptedMessage = ""
        for word in plainText:
            DecryptedMessage += PlayFairDecryption(word,Matrix) + " "
        print(DecryptedMessage)

#This function gets the main input of the simulation
def Input():
    Method = int(input("Enter The Method no. { 1- Encryption 2- Decryption } : "))
    while(Method not in [1,2]):
        Method = int(input("Enter The Method no. { 1- Encryption 2- Decryption } : "))
    return Method
#The main function
while True:
    plainText = input("Text : ")
    print("Enter The no. of Methodology you want : \n 1- Caesar Cipher 2- PlayFair")
    methodology = int(input("Please Enter The number : "))
    if methodology == 1:
        CaesarCipher(plainText)
    elif methodology == 2 :
        PlayFair(plainText)

    if input("Want to continue [Yy/Nn] : ") in ['N','n'] :
        break
    else:
        continue 
        
