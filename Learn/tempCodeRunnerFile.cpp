readFromBinary("usr.dat",user);
    for(int i=0;i<user.getLength();i++){
        user.getValue(i).displayInfo();
    }