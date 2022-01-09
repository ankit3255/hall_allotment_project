#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class Room
{
    private:
    map< int,pair < vector < string > ,int >> mp;   // map stores the data of name room number and room type 
    bool check_room_no(int);                        // function to check room number valid  or not
    bool check_room_type(int);                      // function to check room type is valid or not

    public:
    Room()
    {
        ifstream fio;                           // read a file
        fio.open("dataframe.txt");              // open  a file in read mode 
        while(fio) {      
            vector< string > st;                //using while for inserting data into map till the endline in file
            string temp;
            int num1,num2;
            
            fio >> num1 >> num2;                // read the room number and room type from file      
            getline(fio, temp);                 // read the name of students in string  temp
            istringstream ss(temp);             // split the string using istringstream
            
            string word;
            while(ss >> word){                  // using ss stream to read  temp
                st.push_back(word);
            }
            
            mp.insert({num1,{st,num2}});         // insert the data into map
        }
        fio.close();
    }    
    

    
    void get_details(int);
    void show_all_details();
    void deallot_room(int,string);
    void allot_room(string,int,int);
    void get_vacant_room_details_type(int);
    

    ~Room(){                                     // make a destructor to write in file
        ofstream fin;                            // write in file
        fin.open("dataframe.txt",ios::trunc);    // open file
           
        for(auto i:mp){                          //acsessing the data from map and inserting the data into file
                 
            fin << i.first << " " << i.second.second << " ";
            for(auto j:i.second.first){
                fin << j <<" ";
            }

            fin<<endl;
        }
            
        fin.close();                            // and close the file

    }
};

bool Room::check_room_no(int x){
    if((x >= 101) && (x <= 120))   // checking the room number valid or not     
        return true;
    else  
        return false;    
}
 
 bool Room::check_room_type(int x){
    if((x>=1) && (x<=3))                // checking the room type valid or not
        return true;
    else
        return false;

 }
void Room::get_details(int x)
{    // find details of a particular room by using room number
    if (check_room_no(x) == false)  {
        cout<<"error room not found \n";
        return;
    }

    
    if(mp[x].first.size()==0) {
        cout<<" room is empty \n";
    }
    else {
        cout <<" In Room No: " << x << " Room type: "<< mp[x].second;
        cout<<" name of students:  ";
        for(auto i:mp[x].first) {
            cout << i << endl;
        }
    }

}
 void Room::show_all_details()
{
   for(auto i: mp){
        if(i.second.first.size()!=0){
            cout <<" In Room No : " << i.first << "\n Room type "<< i.second.second;
            cout<<"\n name of students:\n";
            for(auto j: i.second.first){
                 cout << j << endl;
            } 
       
        }
    }          
}

void Room::deallot_room(int y,string name)
{ 
    if(check_room_no(y)==true){ 
           // dealloting the room for a given student name
        if(find(mp[y].first.begin(),mp[y].first.end(),name)!=mp[y].first.end()){
            mp[y].first.erase(remove(mp[y].first.begin(), mp[y].first.end(),name), mp[y].first.end());
            cout<<"successfully dealloted \n";
        }

        else{
            cout<<"this name does not exits in the room\n";
            
        }    
    }

    else{
        cout<<"room number not found \n"; 
    }   
    
}
void Room::allot_room(string x,int roomno,int z)
{  // alloting the room by taking the information of their name ,room type
    if((check_room_no(roomno)==false) || (check_room_type(z)==false)){
        cout<<"error room not found \n";
        return ;
    }
      
    if(mp[roomno].first.size()<z){    // checking the room size
        mp[roomno].first.push_back(x);
        std::cout<<"room alooted successfully \n "<<endl;
    }

    else{
        std::cout<<"this room is full\n";
    }  
    
}
void Room::get_vacant_room_details_type(int t){
    // using room type finding all the deatils is empty
    if(t==1 || t==2 || t==3){
        for(auto i:mp){
            if(i.second.second==t){
                if(i.second.first.size()<t){
                    cout<< "room No"<<i.first<<" total vacant seats :"<<t-i.second.first.size()<< endl;
                    
                }
            }
        }
    }
    
    else {  
        cout<<"type room number value 1,or,2,or,3 \n";
    }
}


int main(){

    Room s2;
    cout<<" ********* Hostel Room Allotment ********* \n";
    cout<<" 1. Room Number"<<endl;
    cout<<" 2. Show all details"<<endl;
    cout<<" 3. Deallot room"<<endl;
    cout<<" 4. Allot Room number"<<endl;
    cout <<" 5. View details of empty rooms \n";
    cout<< " 6. Quit \n";
    int choice;
    cout<<"Enter the choice: ";
    cin>>choice;
    while(choice!=6) {
        switch (choice) {
        case  1:{
            int x;
            cout<<"Enter the Room Number: ";
            cin>>x;
            s2.get_details(x);
            break;
        }

        case 2:{
            s2.show_all_details();
            break;
        }

        case 3:{
            int y;
            string name;
            cout<<"Enter the room number : ";
            cin>>y;
            cout<<"Enter the name: ";
            cin>>name;
            s2.deallot_room(y,name);
            break;
            
        }

        case 4:{
            string r;
            cout<<"Enter the  student name: ";
            cin>>r;
            int l;
            cout<<"Type of room enter numerical value: ";
            cin>>l;
            int roomno;
            cout<<"Enter the room number: ";
            cin>>roomno;
            s2.allot_room(r,roomno,l);
            break;
            
        }
        case 5:
        {
            int f;
            cout << "Enter the Room type : ";
            cin>>f;
            s2.get_vacant_room_details_type(f);
            break;
        }

        case 6:
           {
                s2.~Room();      
                exit(0);
                break;

               
            }

        default:
           { cout<<"Enter the valid choice : ";
             break;
            }
        }
        cout<<"Enter the choice: ";
    cin>>choice;
    }
}