#include"../utils/User.hpp"
int main(){
    ArrayList<User> user;
    // readFromCV("../Data/generated_records.csv",user,"usr.dat");
    readFromBinary("usr.dat",user);
    for(int i=0;i<user.getLength();i++){
        user.getValue(i).displayInfo();
    }
    return 0;
}