//nice
#include<iostream>
#include"utils/User.hpp"

#define USER_FILE "user.bin"
int User::numberOfUser = 0;
int main(){
    ArrayList<User> user;
    User tempUser;
    
    tempUser.input(USER_FILE);
    user.push(tempUser);
    writeToBinary(USER_FILE,user);

    tempUser.input(USER_FILE);
    user.push(tempUser);
    writeToBinary(USER_FILE,user);

    // readFromBinary(USER_FILE,user);
    // for(int i=0;i<user.getLength();i++){
    //     tempUser=user.getValue(i);
    //     tempUser.output();
    }

    return 0;
}