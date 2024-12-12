 vector<User> user;
    readFromCV("../Data/custom_generated_data.csv",user,"../Data/usr.dat");
    readFromBinary("../Data/usr.dat",user);
    for(int i=0;i<user.size();i++){
        user.at(i).displayInfo();
    }