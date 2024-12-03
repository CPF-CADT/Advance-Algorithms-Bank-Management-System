   for show run code below
   system(command1);
   readFromBinary(USER_FILE,user);
   for(int i=0;i<user.getLength();i++){
      tempUser=user.getValue(i);
      tempUser.output();
   }