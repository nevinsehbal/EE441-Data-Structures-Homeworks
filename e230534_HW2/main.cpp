#include <iostream>
#include <fstream>
#include<string.h>

using namespace std;

/*
* "Student" class
* Members:
* Student ID,
* Section Preferences (3)
*/
class Student {
    private:
        int mStuId;
        char mPreferences[3] = {0,0,0};
    public:
        Student(int stu_id, char preferences[3]);
        Student() = default;
        int GetID() const;
        char GetFirstPreference();
        char *GetPreferences();
        void SetID(int stu_id);
        void SetPreferences(char preferences[3]);
        int NumOfAvailableSect();
};

/*
* "Stack" class
* Members:
* MaxSize, student list, top student
*/
class Stack{
    private:
        int MaxSize;
        Student slist[100];
        int top = 0;
    public:
        Stack();
        int SLength(void)const;
        void setSize (int section_size);
        void push (const Student &stu);
        Student pop (void);
        bool isFull (void);
};

/*
* "Queue" class, circular type
* Members:
* FRONT, REAR, counter, Max Size, Student list
*/
class Queue{
    private:
        int FRONT, REAR,counter;
        int const MaxQSize = 100;
        Student qlist[100];
    public:
        Queue(void);
        int QFull(void) const;
        int QLength(void) const;
        int QEmpty(void) const;
        void QInsert(const Student &stu);
        Student QRemove(void);
        Student QFront(void) const;
        int QLenght(void) const;
};

// Global declaration of three section stacks
// so that student class objects can use
Stack WedStack;
Stack ThuStack;
Stack FriStack;

int main(){

    // Waiting queue object creation
    Queue Waiting;

    int fri_size = 0;
    int wed_size = 0;
    int thu_size = 0;

    // in.txt file read section
    char delimeter = ',';
    ifstream inputtxt;
    inputtxt.open("in.txt");

    char out[100];
    if (inputtxt.is_open()) {
        int i = 0;
        while (i != 3) {
            inputtxt >> out;
            char day;
            char *s;
            int capacity;
            s = strtok(out, ",");
            if(s) sscanf(s, "%c", &day);
            s = strtok(NULL, ",");
            if(s) sscanf(s, "%d", &capacity);
            if(day == 'F') fri_size = capacity;
            if(day == 'W') wed_size = capacity;
            if(day == 'T') thu_size = capacity;
            i++;
        }
    }

    // Section stack size setting
    WedStack.setSize(wed_size);
    ThuStack.setSize(thu_size);
    FriStack.setSize(fri_size);

    // Start reading student information from file in.txt
    // Assign students with one preferences to empty sections
    // Insert remaining students to waiting queue until the end of in.txt
    while(1){
        if (inputtxt.is_open()){
        inputtxt >> out;
        }

        int id;
        char days[3] = {0,0,0};

        // Split the line into ID and preferences (char array[3])
        char *p;
        p = strtok(out, ",");
        if(p){ sscanf(p, "%d", &id);}
        p = strtok(NULL, ",");
        if(p){sscanf(p, "%c", &days[0]);}
        p = strtok(NULL, ",");
        if(p){sscanf(p, "%c", &days[1]);}
        p = strtok(NULL, ",");
        if(p){sscanf(p, "%c", &days[2]);}

        // Create the student
        Student currentStu(id,days);
        char first;
        char *prefs;
        prefs = currentStu.GetPreferences();
        char first_pref = *prefs;
        char second_pref = *(prefs+1);
        char third_pref = *(prefs+2);

        int num_of_prefs_available;
        num_of_prefs_available = currentStu.NumOfAvailableSect();

        // assign the one preference students to empty stacks
        if(num_of_prefs_available == 1 && !second_pref && !third_pref){
            if(first_pref=='W') WedStack.push(currentStu);
            if(first_pref=='T') ThuStack.push(currentStu);
            if(first_pref=='F') FriStack.push(currentStu);
        }
        // otherwise, put them into waiting queue
        else Waiting.QInsert(currentStu);

        //If file read is finished, break the while loop and start writing process.
        if(inputtxt.eof()){
                break;
        }
    }

    // while loop to check and assign students with two preferences from the line
    int QLen = Waiting.QLength();
    while(QLen != 0){
        QLen--;
        Student tmpStu;
        tmpStu = Waiting.QFront();

        char *tmp_prefs;
        tmp_prefs = tmpStu.GetPreferences();
        char tmp_first = *tmp_prefs;
        char tmp_second = *(tmp_prefs+1);
        char tmp_third = *(tmp_prefs+2);

        if(!tmp_third){ // if third preference does not exist

            if(tmp_first=='W'){
                if(!(WedStack.isFull())) WedStack.push(tmpStu);
                else if(tmp_second=='T' && !(ThuStack.isFull())) ThuStack.push(tmpStu);
                else if(tmp_second=='F' && !(FriStack.isFull())) FriStack.push(tmpStu);
                else Waiting.QInsert(tmpStu);
            }

            if(tmp_first=='T'){
                if(!(ThuStack.isFull())) ThuStack.push(tmpStu);
                else if(tmp_second=='W' && !(WedStack.isFull())) WedStack.push(tmpStu);
                else if(tmp_second=='F' && !(FriStack.isFull())) FriStack.push(tmpStu);
                else Waiting.QInsert(tmpStu);
            }

            if(tmp_first=='F'){
                if(!(FriStack.isFull())) FriStack.push(tmpStu);
                else if(tmp_second=='W' && !(WedStack.isFull())) WedStack.push(tmpStu);
                else if(tmp_second=='T' && !(ThuStack.isFull())) ThuStack.push(tmpStu);
                else Waiting.QInsert(tmpStu);
            }
        }
        else Waiting.QInsert(tmpStu);
        Waiting.QRemove();
    }

    // while loop to check and assign students with three preferences
    int Q2Len = Waiting.QLength();
    while(Q2Len != 0){
        Q2Len--;
        Student tmp2Stu;
        tmp2Stu = Waiting.QFront();
        char *tmp2_prefs;
        tmp2_prefs = tmp2Stu.GetPreferences();
        char tmp2_first = *tmp2_prefs;
        char tmp2_second = *(tmp2_prefs+1);
        char tmp2_third = *(tmp2_prefs+2);

        if(tmp2_first=='W'){
                if(!(WedStack.isFull())) WedStack.push(tmp2Stu);
                else{
                    if(tmp2_second=='T'){
                        if(!(ThuStack.isFull())) ThuStack.push(tmp2Stu);
                        else if(tmp2_third == 'F'&& !(FriStack.isFull())) FriStack.push(tmp2Stu);
                        else Waiting.QInsert(tmp2Stu);
                    }
                    else if(tmp2_second == 'F'){
                        if(!(FriStack.isFull())) FriStack.push(tmp2Stu);
                        else if(tmp2_third == 'T'&& !(ThuStack.isFull())) ThuStack.push(tmp2Stu);
                        else Waiting.QInsert(tmp2Stu);
                    }
                    else Waiting.QInsert(tmp2Stu);
                }
        }

        if(tmp2_first=='T'){
                if(!(ThuStack.isFull())) ThuStack.push(tmp2Stu);
                else{
                    if(tmp2_second=='W'){
                        if(!(WedStack.isFull())) WedStack.push(tmp2Stu);
                        else if(tmp2_third == 'F'&& !(FriStack.isFull())) FriStack.push(tmp2Stu);
                        else Waiting.QInsert(tmp2Stu);
                    }
                    else if(tmp2_second == 'F'){
                        if(!(FriStack.isFull())) FriStack.push(tmp2Stu);
                        else if(tmp2_third == 'W'&& !(WedStack.isFull())) WedStack.push(tmp2Stu);
                        else Waiting.QInsert(tmp2Stu);
                    }
                    else Waiting.QInsert(tmp2Stu);
                }
        }

        if(tmp2_first=='F'){
                if(!(FriStack.isFull())) FriStack.push(tmp2Stu);
                else{
                    if(tmp2_second=='W'){
                        if(!(WedStack.isFull())) WedStack.push(tmp2Stu);
                        else if(tmp2_third == 'T'&& !(ThuStack.isFull())) ThuStack.push(tmp2Stu);
                        else Waiting.QInsert(tmp2Stu);
                    }
                    else if(tmp2_second == 'T'){
                        if(!(ThuStack.isFull())) ThuStack.push(tmp2Stu);
                        else if(tmp2_third == 'W'&& !(WedStack.isFull())) WedStack.push(tmp2Stu);
                        else Waiting.QInsert(tmp2Stu);
                    }
                    else Waiting.QInsert(tmp2Stu);
                }
        }
        Waiting.QRemove();
    }

    // write to out.txt section
    ofstream outputtxt;
    outputtxt.open("out.txt");

    int WedStackSize = WedStack.SLength();
    int WedWriteSize = WedStackSize;
    int ThuStackSize = ThuStack.SLength();
    int ThuWriteSize = ThuStackSize;
    int FriStackSize = FriStack.SLength();
    int FriWriteSize = FriStackSize;

    // writeTxt stack is created to reverse the section stacks,
    // so that the order of assignment is not disturbed
    Stack writeTxtStack;
    Student writeStu;
    int writeStuId;

    writeTxtStack.setSize(WedStackSize);
    outputtxt<<"Wednesday:\n";
    // Wednesday section stack push to another stack in order to reverse the order
    while(WedStackSize!=0){
        writeStu = WedStack.pop();
        writeStuId = writeStu.GetID();
        writeTxtStack.push(writeStu);
        WedStackSize--;
    }
    // Wednesday Group out.txt writing process
    while(WedWriteSize!=0){
        writeStu = writeTxtStack.pop();
        writeStuId = writeStu.GetID();
        outputtxt<<writeStuId<<"\n";
        WedWriteSize--;
    }

    // Thursday section stack push to another stack in order to reverse the order
    writeTxtStack.setSize(ThuStackSize);
    outputtxt<<"\nThursday:\n";
    while(ThuStackSize!=0){
        writeStu = ThuStack.pop();
        writeStuId = writeStu.GetID();
        writeTxtStack.push(writeStu);
        ThuStackSize--;
    }
    // Thursday Group out.txt writing process
        while(ThuWriteSize!=0){
        writeStu = writeTxtStack.pop();
        writeStuId = writeStu.GetID();
        //cout<<writeStuId<<endl;
        outputtxt<<writeStuId<<"\n";
        ThuWriteSize--;
    }

    // Friday section stack push to another stack in order to reverse the order
    writeTxtStack.setSize(FriStackSize);
    outputtxt<<"\nFriday:\n";
    while(FriStackSize!=0){
        writeStu = FriStack.pop();
        writeStuId = writeStu.GetID();
        writeTxtStack.push(writeStu);
        FriStackSize--;
    }
    // Friday Group out.txt writing process
        while(FriWriteSize!=0){
        writeStu = writeTxtStack.pop();
        writeStuId = writeStu.GetID();
        outputtxt<<writeStuId<<"\n";
        FriWriteSize--;
    }

    // Unassigned Group out.txt writing process
    int WaitingSize = Waiting.QLength();
    outputtxt<<"\nUnassigned:\n";
    if(Waiting.QEmpty()) outputtxt<<"-\n";

    else {
    while(WaitingSize!=0){
        writeStu=Waiting.QRemove();
        writeStuId=writeStu.GetID();
        outputtxt<<writeStuId<<"\n";
        WaitingSize--;
    }}

    outputtxt.close();
    return 0;
}

/*
    Student class constructor
*/
Student::Student(int stu_id, char preferences[3])
{
            mStuId = stu_id;
            for(int j=0;j<3;j++){
                mPreferences[j] = preferences[j];
            }
}

/*
    Definition: Getter function for student ID
    @Parameters: none
    @Return: Student ID private member
*/
int Student::GetID() const {
    return mStuId;
}

/*
    Definition: Getter function for student homework scores
    @Parameters: none
    @Return: Private member: homework score array's pointer
*/
char *Student::GetPreferences(){
    return mPreferences;
}

char Student::GetFirstPreference(){
    return mPreferences[0];
}

int Student::NumOfAvailableSect(){
    int available_num = 0;
    char *pt = GetPreferences();
    char first = *pt;
    char second = *(pt+1);
    char third = *(pt+2);
    if((first == 'W' || second == 'W' || third == 'W') && !(WedStack.isFull())){
        available_num++;
    }
    if((first == 'T' || second == 'T' || third == 'T') && !(ThuStack.isFull())){
        available_num++;
    }
    if((first == 'F' || second == 'F' || third == 'F') && !(FriStack.isFull())){
        available_num++;
    }
    return available_num;
}

Stack::Stack(){
    top = -1;
}

int Stack::SLength(void)const{
    return (top+1);
}

void Stack::setSize(int section_size){
    MaxSize = section_size;
}

void Stack::push(const Student &stu){
    if(top>=(MaxSize-1)){
        cerr<<"Stack Overflow";
        //exit(1);
    }
    else{
        slist[++top] = stu;
        //cout<<" Stack pushed into stack\n";;
    }
}

Student Stack::pop(void){
    if(top<0){
        cerr<<"Stack Underflow";
        exit(1);
    }
    else{
        Student stu = slist[top--];
        return stu;
    }
}

bool Stack::isFull(void){
    return (top == MaxSize-1);
}


Queue::Queue(void){
    FRONT = 0;
    REAR = 0;
    counter = 0;
}

int Queue::QLength(void)const{
    return counter;
}

int Queue::QFull(void) const{
    return (counter==MaxQSize);
}

int Queue::QEmpty(void) const{
    return (counter==0);
}

void Queue::QInsert(const Student &stu){
    if (QFull()){
        cerr<<"Queue overflow"<<endl;
        exit(1);
    }
    counter++;
    qlist[REAR]=stu;
    REAR = (REAR+1)%MaxQSize;
}

Student Queue::QRemove(void){
    Student temp;
    if (QEmpty()){
        cerr<<"Cannot delete from an empty queue"<<endl;
        exit(1);
    }
    temp = qlist[FRONT];
    counter--;
    FRONT = (FRONT+1)%MaxQSize;
    return temp;
}

Student Queue::QFront(void) const{
    return qlist[FRONT];
}
