#include"../utils/User.hpp"
int main(){
    ArrayList<User> user;
    // readFromCV("../Data/generated_records.csv",user,"../Data/usr.dat");
    readFromBinary("../Data/usr.dat",user);
    for(int i=0;i<user.getLength();i++){
        user.getValue(i).displayInfo();
    }
    return 0;
}