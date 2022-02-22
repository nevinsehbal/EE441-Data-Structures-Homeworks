#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#define MAX_SIZE 10

/*
* "Student" class
* Members:
* Student ID, Name, Surname,
* Quiz Scores (4), Homework Scores (3), Final Grade
* Contains function to calculate weighted overall grade of the student
*/
class Student {
    private:
        int mStuId;
        string mName, mSurname;
        float mQuizScores[4] = {0,0,0,0};
        float mHwScores[3] = {0,0,0};
        float mFinalScore = 0;
    public:
        Student(int stu_id, string name, string surname, float quiz_scores[4], float hw_scores[3], float final_score);
        Student() = default;
        int GetID() const;
        string GetName() const;
        string GetSurname() const;
        float *GetQuizScores();
        float *GetHwScores();
        float GetFinalScore() const;
        void SetID(int stu_id);
        void SetNameSurname(string name,string surname);
        void SetQuizScores(float quiz_scores[4]);
        void SetHwScores(float hw_scores[3]);
        void SetFinalScore(float final_score);
        float OverallCourseScore(void) const;
};


/*
* "Course" class inherited from "Student" class
* Members:
* Students[Maximum 10 student], Current Number of Students,
* Quizzes weight, Homeworks weight, Final weight,
* Includes:
* function to add a new student,
* function to update course weights,
* function to show student's info,
* function to get student's info,
* function to calculate weighted class average for quizzes, homeworks and final
*/
class Course:Student
{
    private:
        Student mStudents[MAX_SIZE];
        int mCurrentNumStudent = 0;
        float mWeightQuiz = 0.3;
        float mWeightHw = 0.3;
        float mWeightFinal = 0.4;
    public:
        Course(float weightQuiz, float weightHw, float weightFinal);
        int getNum(void) const;
        float getQuizWeight(void) const;
        float getHwWeight(void) const;
        float getFinalWeight(void) const;
        bool addNewStudent(int stu_id, string name, string surname);
        void updateWeights(float weightQuiz, float weightHw, float weightFinal);
        void showStudent(int stu_id) const;
        Student getStudentInfo(int stu_id) const;
        void calculateAverage(void);
        Student* getStudentsList(void);
};

/*
    Definition: Finds the student's index
    from the Student's list.
    @parameters: Student's ID, Current number of students, Students' list
    @return: index of the student in the student list
*/
int get_index_by_id(int id, int numOfStudents, Student *stu_list){
            int current_index;
            for(int i=0; i<numOfStudents;i++){
                int current_id = (stu_list)[i].GetID();
                if(current_id == id) current_index = i;
            }
            return current_index;
        }

/*
    Definition: Splits a string into separate strings from spaces(" ").
    @parameters: String
    @return: A string vector
*/
std::vector<string> string_split(const string& str) {
	vector<string> result;
	std::istringstream iss(str);
	for (std::string s; iss >> s; )
		result.push_back(s);
	return result;
}


/*
    Definition: Checks if the string only contains digits and "."
    @parameters: String
    @return: bool
*/
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789.") == std::string::npos;
}

/*
    Definition: Checks if the string only contains letters.
    @parameters: String
    @return: bool
*/
bool is_letters(string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]);
		if (uppercaseChar < 'A' || uppercaseChar > 'Z')
		{
			return false;
		}
	}
	return true;
}

/*
    Definition: Checks if a student with an id exists in the Student list.
    @parameters: Student list, current number of students, ID
    @return: bool
*/
bool is_id_exists(Student *stu, int numOfStu, int id){
    bool id_found;
    for(int i=0;i<numOfStu;i++){
        if(stu[i].GetID() == id) id_found=1;
    }
    if(id_found) return 1;
    else return 0;
}

// "myCourse" object construction from Course class
Course myCourse(0.3,0.3,0.4);


/*
    The program switches between cases as long as "exit" option is not chosen.
    Options:
    1.Add student
    2.Search a student by ID
    3.Change a student's score
    4.Update exam weigths
    5.Show classroom average
    6.Show students with overall score below a threshold
    7.Show students with overall score above a threshold
    8.Exit
*/
int main()
{
    int currentOption = 0;
    cout<<"\nWelcome to EE441 Information Center\n"<<endl;
    cout<<"Please choose one of the options below:"<<endl;
    cout<<"\n1.Add student"<<endl<<"2.Search a student by ID"<<endl;
    cout<<"3.Change a student's score"<<endl<<"4.Update exam weigths"<<endl;
    cout<<"5.Show classroom average"<<endl<<"6.Show students with overall score below a threshold"<<endl;
    cout<<"7.Show students with overall score above a threshold"<<endl;
    cout<<"8.Exit"<<endl;

    while(1)
    {
        int error_flag = 0;
        cout<<"\nEnter your option: ";
        cin>>currentOption;
        if(cin.fail() || currentOption>8 || currentOption<1) // if current option is not valid
        {
            cin.clear();
            cout<<"\nInvalid option, try again!"<<endl;
            cin.ignore(1000, '\n');
            continue;
        }

        switch (currentOption)
        {

        /*
        Case 1: Gets the information of the student to be added.
        Checks if the input size and format is correct.
        Does not add if new ID number is same with another student
        Does not add if MAX SIZE is reached in the course.
        */
         case 1:{
            cout<<"\n ----- Add student ----- "<<1<<endl;
            string all_info;
            cout<<"\nEnter student's ID, name, surname and scores (quizzes, homeworks, final)"<<endl;
            cin.ignore();
            getline(cin, all_info);
            if(all_info =="") continue;
            std::vector<std::string> myVect;
            myVect = string_split(all_info);

            if(myVect.size() != 11){
                cout<<"\nInvalid input! Accepted format is: \"id name surname Q1 Q2 Q3 Q4 HW1 HW2 HW3 Final\""<<endl;
                cout<<"Note: Only English letters are valid."<<endl;
                cout<<"Returning to the home page.."<<endl;
                continue;
            };

            if(is_digits(myVect[0]) != 1) error_flag = 1;

            for(int i=0;i<7;i++) if(is_digits(myVect[i+3]) != 1) error_flag = 1;

            if(!is_letters(myVect[1]) || !is_letters(myVect[2])) error_flag = 1;

            if(error_flag){
                cout<<"\nInvalid input! Accepted format is: \"id name surname Q1 Q2 Q3 Q4 HW1 HW2 HW3 Final\""<<endl;
                cout<<"Note: Only English letters are valid."<<endl;
                cout<<"Returning to the home page.."<<endl;
                error_flag = 0;
                continue;
            }

            int _id;
            string _name = myVect[1];
            string _surname = myVect[2];
            float quiz[4]={0,0,0,0};
            float hw[3] = {0,0,0};
            float fin = 0;

            sscanf(myVect[0].c_str(), "%d", &_id);

            Student *stu = myCourse.getStudentsList();
            int num_of_stu = myCourse.getNum();
            if(is_id_exists(stu,num_of_stu,_id) == 1){
                cout<<"\nYou cannot add an existing user! Returning to the home page.."<<endl;
                continue;
            }

            for(int i=0;i<4;i++){
                sscanf(myVect[i+3].c_str(), "%f", &quiz[i]);
                if(quiz[i]<0 || quiz[i]>100) error_flag = 1;
            }

            for(int i=0;i<3;i++){
                sscanf(myVect[i+7].c_str(), "%f", &hw[i]);
                if(hw[i]<0 || hw[i]>100) error_flag = 1;
            }

            sscanf(myVect[10].c_str(), "%f", &fin);
            if(fin<0 || fin>100) error_flag = 1;

            if(error_flag){
                cout<<"\nInvalid score input! Scores must be digit and in the range 0-100"<<endl;
                cout<<"Returning to the home page.."<<endl;
                error_flag = 0;
                continue;
            }

            bool max_student = 0;
            max_student = myCourse.addNewStudent(_id,_name,_surname);
            if(max_student == 0){
                cout<<"\nMaximum number of students have been reached! You cannot add."<<endl;
                continue;
            }

            Student *stu_list = myCourse.getStudentsList();
            int numOfStudents = myCourse.getNum();

            int current_index;
            current_index = get_index_by_id(_id, numOfStudents, stu_list);

            (stu_list)[current_index].SetQuizScores(quiz);
            (stu_list)[current_index].SetHwScores(hw);
            (stu_list)[current_index].SetFinalScore(fin);

            cout<<"\nStudent "<<_id<<" - "<<_name<<" "<<_surname<<" is added successfully!"<<endl;
            //myCourse.showStudent(_id);
            break;}

        /*
        Case 2: Searches and displays a student's info by asking his/her ID.
        Checks if the input size and format is correct.
        Checks if the entered ID exists
        Displays the id, name, surname, quizzes/homeworks/final/overall grade.
        */
         case 2: {
            cout<<"\n ----- Search a student by ID ----- "<<2<<endl;
            cout<<"Enter ID: ";
            string search_id_Str;
            int search_id;
            cin.ignore();
            getline(cin, search_id_Str);
            if(search_id_Str=="") continue;

            if(is_digits(search_id_Str)!= 1){
                cout<<"\nInvalid input! Returning to the home page.."<<endl;
                continue;
            }
            sscanf(search_id_Str.c_str(), "%d", &search_id);

            Student *stu = myCourse.getStudentsList();
            int num_of_stu = myCourse.getNum();
            if(is_id_exists(stu,num_of_stu,search_id) != 1){
                cout<<"\nThis student does not exist! Returning to the home page.."<<endl;
                continue;
            }

            myCourse.showStudent(search_id);
            break;
         }

        /*
        Case 3: Changes a student's scores by asking his/her ID.
        Checks if the input size and format is correct.
        Checks if the entered ID exists
        Checks if the scores are in the range 0-100
        Then, updates scores.
        */
         case 3: {
            cout<<"\n ----- Change a student's score -----"<<3<<endl;
            cout<<"Enter ID: ";
            string score_id_Str;
            int score_id;
            cin.ignore();
            getline(cin, score_id_Str);
            if(score_id_Str=="") continue;

            if(is_digits(score_id_Str)!= 1){
                cout<<"\nInvalid input! Returning to the home page.."<<endl;
                continue;
            }

            sscanf(score_id_Str.c_str(), "%d", &score_id);

            Student *stu = myCourse.getStudentsList();
            int num_of_stu = myCourse.getNum();
            if(is_id_exists(stu,num_of_stu,score_id) != 1){
                cout<<"\nInvalid ID input! Returning to the home page.."<<endl;
                continue;
            }

            string scoreStr;
            cout<<"\nEnter student's scores (quizzes, homeworks, final)"<<endl;
            getline(cin, scoreStr);
            std::vector<std::string> scoreVect;
            scoreVect = string_split(scoreStr);

            if(scoreVect.size() != 8){
                cout<<"\nInvalid input! Accepted format is: \"Q1 Q2 Q3 Q4 HW1 HW2 HW3 Final\""<<endl;
                cout<<"Returning to the home page.."<<endl;
                continue;
            };

            for(int i=0;i<8;i++) if(is_digits(scoreVect[i]) != 1) error_flag = 1;

            float quiz[4]={0,0,0,0};
            float hw[3] = {0,0,0};
            float fin = 0;

            for(int i=0;i<4;i++){
                sscanf(scoreVect[i].c_str(), "%f", &quiz[i]);
                if(quiz[i]<0 || quiz[i]>100) error_flag = 1;
            }
            for(int i=0;i<3;i++){
                sscanf(scoreVect[i+4].c_str(), "%f", &hw[i]);
                if(hw[i]<0 || hw[i]>100) error_flag = 1;
            }
            sscanf(scoreVect[7].c_str(), "%f", &fin);
            if(fin<0 || fin>100) error_flag = 1;

            if(error_flag){
                cout<<"\nInvalid score input! Scores must be in the range 0-100"<<endl;
                cout<<"Returning to the home page.."<<endl;
                error_flag = 0;
                continue;
            }

            Student *stu_list = myCourse.getStudentsList();
            int numOfStudents = myCourse.getNum();

            int current_index;
            current_index = get_index_by_id(score_id, numOfStudents, stu_list);

            (stu_list)[current_index].SetQuizScores(quiz);
            (stu_list)[current_index].SetHwScores(hw);
            (stu_list)[current_index].SetFinalScore(fin);
            cout<<"Scores are set successfully!"<<endl;
            break; }

        /*
        Case 4: Updates exam weights.
        Checks if the input size and format is correct.
        Checks if the weights are in the range 0-1
        Checks if the weights sum is equal to 1.
        Then, updates weights.
        */
         case 4:{
            bool err_flag = 0;
            cout<<"\n -------- Update exam weigths --------- "<<4<<endl;
            cout<<"Enter weights for quizzes, homeworks and final: "<<endl;
            float quizW, homeworkW, finalW;
            string weightStr;
            cin.ignore();
            getline(cin, weightStr);
            std::vector<std::string> weightVect;
            weightVect = string_split(weightStr);
            sscanf(weightVect[0].c_str(), "%f", &quizW);
            sscanf(weightVect[1].c_str(), "%f", &homeworkW);
            sscanf(weightVect[2].c_str(), "%f", &finalW);

            bool is_out_of_range = (quizW<0 || quizW>1 || homeworkW<0 || homeworkW>1 || finalW<0 || finalW>1);
            float sum_check = quizW+homeworkW+finalW;
            bool is_sum_not_one = ((sum_check)!=1);
            if(is_out_of_range || is_sum_not_one) err_flag=1;
            if(err_flag){
                cout<<"\nInvalid score input! Scores must be digit and in the range 0-1"<<endl;
                cout<<"Returning to the home page.."<<endl;
                err_flag = 0;
                continue;
            }
            myCourse.updateWeights(quizW,homeworkW,finalW);
            cout<<"Weights are updated successfully!"<<endl;
            break;}

        /*
        Case 5: Shows classroom average for quizzes, homeworks and final.
        */
         case 5:
            cout<<"\n ------------ Show classroom average --------- "<<5<<endl;
            myCourse.calculateAverage();
            break;

        /*
        Case 6: Shows students with overall score below a certain threshold
        Checks if the input size and format is correct.
        Checks if the threshold is in the range 0-100.
        Then, shows all of the students below this threshold with their overall grades.
        */
         case 6:{
            cout<<"\n ---- Show students with overall score below a threshold ---- "<<6<<endl;
            bool no_stu_flag = 0;
            string threshold_Str;
            float threshold = 0;
            cout<<"Enter threshold: ";
            cin.ignore();
            getline(cin, threshold_Str);
            if(threshold_Str=="") continue;

            if(is_digits(threshold_Str)!= 1){
                cout<<"\nInvalid input! Returning to the home page.."<<endl;
                continue;
            }

            sscanf(threshold_Str.c_str(), "%f", &threshold);

            if(threshold<0 || threshold>100){
                cout<<"\nInvalid threshold! It must be between 0-100"<<endl;
            }

            Student *stu_list = myCourse.getStudentsList();
            int numOfStu = myCourse.getNum();
            if(numOfStu == 0){
                cout<<"\nNo students in the class! Returning to home page.."<<endl;
                continue;
            }
            float student_overall_grade;
            for(int i=0;i<numOfStu;i++){
                student_overall_grade = (stu_list)[i].OverallCourseScore();
                int id = stu_list[i].GetID();
                if(student_overall_grade < threshold) myCourse.showStudent(id);
                else no_stu_flag = 1;
            }
            if(no_stu_flag){
                cout<<"\nNo student below "<<threshold<<" score"<<endl;
                no_stu_flag = 0;
            }
            break;}

        /*
        Case 7: Shows students with overall score above a certain threshold
        Checks if the input size and format is correct.
        Checks if the threshold is in the range 0-100.
        Then, shows all of the students above this threshold with their overall grades.
        */
         case 7:{
            cout<<"\n ---- Show students with overall score above a threshold ---- "<<6<<endl;
            bool no_stu_flag = 0;
            string threshold_Str;
            float threshold = 0;
            cout<<"Enter threshold: ";
            cin.ignore();
            getline(cin, threshold_Str);
            if(threshold_Str=="") continue;

            if(is_digits(threshold_Str)!= 1){
                cout<<"\nInvalid input! Returning to the home page.."<<endl;
                continue;
            }
            sscanf(threshold_Str.c_str(), "%f", &threshold);

            Student *stu_list = myCourse.getStudentsList();
            int numOfStudents = myCourse.getNum();
            if(numOfStudents == 0){
                cout<<"\nNo students in the class! Returning to the home page.."<<endl;
                continue;
            }
            float student_overall_grade;
            for(int i=0;i<numOfStudents;i++){
                student_overall_grade = (stu_list)[i].OverallCourseScore();
                int id = stu_list[i].GetID();
                if(student_overall_grade > threshold) myCourse.showStudent(id);
                else no_stu_flag = 1;
            }
            if(no_stu_flag){
                cout<<"\nNo student below "<<threshold<<" score"<<endl;
                no_stu_flag = 0;
            }
            break;}

        /*
        Case 8: Exits the program.
        */
          case 8: {
                cout<<"\nProgram closed."<<endl;
                return 0;
          break;}

         default:
            int a=0;
      }
    }

    return 0;
}


/*
    Student class constructor
*/
Student::Student(int stu_id, string name, string surname, float quiz_scores[4], float hw_scores[3], float final_score)
{
            mStuId = stu_id;
            mName = name;
            mSurname = surname;
            for(int i=0;i<4;i++){
                mQuizScores[i] = quiz_scores[i];
            }
            for(int j=0;j<3;j++){
                mHwScores[j] = hw_scores[j];
            }
            mFinalScore = final_score;
    }

/*
    Course class constructor
*/
Course::Course(float weightQuiz, float weightHw, float weightFinal){
            mWeightQuiz = weightQuiz;
            mWeightHw = weightHw;
            mWeightFinal = weightFinal;
}

/*
    Definition: Function to set Student ID
    @Parameters: ID
    @Return: none
*/
void Student::SetID(int stu_id){
    mStuId = stu_id;
}

/*
    Definition: Function to set name and surname
    @Parameters: name, surname
    @Return: none
*/
void Student::SetNameSurname(string name, string surname){
    mName = name;
    mSurname = surname;
}

/*
    Definition: Function to set quiz scores
    @Parameters: quiz scores float array size of 4
    @Return: none
*/
void Student::SetQuizScores(float quiz_scores[4]){
    for(int i=0;i<4;i++){
        mQuizScores[i]=quiz_scores[i];
    }
}

/*
    Definition: Function to set homework scores
    @Parameters: quiz scores float array size of 3
    @Return: none
*/
void Student::SetHwScores(float hw_scores[3]){
    for(int i=0;i<4;i++){
        mHwScores[i]=hw_scores[i];
    }
}

/*
    Definition: Function to set final score
    @Parameters: final score type:float
    @Return: none
*/
void Student::SetFinalScore(float final_score){
    mFinalScore = final_score;
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
    Definition: Getter function for student name
    @Parameters: none
    @Return: Private member: student name
*/
string Student::GetName() const{
    return mName;
}

/*
    Definition: Getter function for student surname
    @Parameters: none
    @Return: Private member: student surname
*/
string Student::GetSurname() const{
    return mSurname;
}

/*
    Definition: Getter function for student quiz scores
    @Parameters: none
    @Return: Private member: quiz score array's pointer
*/
float *Student::GetQuizScores(){
    return mQuizScores;
}

/*
    Definition: Getter function for student homework scores
    @Parameters: none
    @Return: Private member: homework score array's pointer
*/
float *Student::GetHwScores(){
    return mHwScores;
}

/*
    Definition: Getter function for student final score
    @Parameters: none
    @Return: Private member: final score
*/
float Student::GetFinalScore() const{
    return mFinalScore;
}

/*
    Definition: Function to calculate overall score of a student
    @Parameters: none
    @Return: weighted mean of quizzes, homeworks and final
*/
float Student::OverallCourseScore() const{
    float quizSum = 0;
    float hwSum = 0;
    float q_wh = myCourse.getQuizWeight();
    float hw_wh = myCourse.getHwWeight();
    float fin_wh = myCourse.getFinalWeight();
    for(int i=0;i<4;i++) quizSum += mQuizScores[i];
    for(int j=0;j<3;j++) {
            hwSum += mHwScores[j];
    }
    float overallScore = (quizSum*q_wh/4)+(hwSum*hw_wh/3)+(mFinalScore*fin_wh);
    return overallScore;
}

/*
    Definition: Getter function for current number of students in the course
    @Parameters: none
    @Return: Private member: number of students
*/
int Course::getNum() const{
    return mCurrentNumStudent;
}

/*
    Definition: Getter function for quizzes weight
    @Parameters: none
    @Return: Private member: quizzes weight
*/
float Course::getQuizWeight(void) const{
    return mWeightQuiz;
}

/*
    Definition: Getter function for homeworks weight
    @Parameters: none
    @Return: Private member: homeworks weight
*/
float Course::getHwWeight(void) const{
    return mWeightHw;
}

/*
    Definition: Getter function for final weight
    @Parameters: none
    @Return: Private member: final weight
*/
float Course::getFinalWeight(void) const{
    return mWeightFinal;
}

/*
    Definition: Adds a new student to the Courses' student list.
    @Parameters: student id, student name, student surname
    @Return: if(course capacity is full) False; else True;
*/
bool Course::addNewStudent(int stu_id, string name, string surname){
    float quiz[4] = {0,0,0,0};
    float hw[3] = {0,0,0};
    float fin = 0;
    Student newStudent(stu_id,name,surname,quiz,hw,fin);
    if(mCurrentNumStudent==MAX_SIZE)return 0;
    mStudents[mCurrentNumStudent] = newStudent;
    mCurrentNumStudent = mCurrentNumStudent + 1;
    return 1;
}

/*
    Definition: Updates weights of the quizzes, homeworks and final
    @Parameters: quiz weight, homework weight, final weight
    @Return: none
*/
void Course::updateWeights(float weightQuiz, float weightHw, float weightFinal){
    mWeightQuiz = weightQuiz;
    mWeightHw = weightHw;
    mWeightFinal = weightFinal;
}

/*
    Definition: Displays a student's all information
    @Parameters: student's ID
    @Return: none
*/
void Course::showStudent(int stu_id) const{
    Student StuDisplay = getStudentInfo(stu_id);
    int iddd = StuDisplay.GetID();
    string dispName = StuDisplay.GetName();
    string dispSurname = StuDisplay.GetSurname();
    float *dispQuiz = StuDisplay.GetQuizScores();
    float *dispHw = StuDisplay.GetHwScores();
    float dispFinal = StuDisplay.GetFinalScore();

    cout<<"\n--------------------- Student Info -------------------------\n"<<endl;
    float overallScore;
    overallScore = StuDisplay.OverallCourseScore();
    cout<<stu_id<<" "<<dispName<<" "<<dispSurname<<" ";
    for(int i=0;i<4;i++){
        cout<<*(dispQuiz+i)<<" ";
    }
    for(int i=0;i<3;i++){
        cout<<*(dispHw+i)<<" ";
    }

    cout<<dispFinal;

    cout<<" Student's overall score is: "<<overallScore<<endl;

    StuDisplay.GetHwScores();

    cout<<"------------------------------------------------------------\n"<<endl;
}

/*
    Definition: Gets a student's all information
    @Parameters: student's ID
    @Return: A student object
*/
Student Course::getStudentInfo(int stu_id) const{
    int stu_idx = 0;
    for(int i=0;i<mCurrentNumStudent;i++){
        int check_id = mStudents[i].GetID();
        if(check_id == stu_id){
            stu_idx = i;
        }}
    string name = mStudents[stu_idx].GetName();
    return mStudents[stu_idx];
    }

/*
    Definition: Calculates and displays the course averages
    for quizzes, homeworks and final
    @Parameters: none
    @Return: none
*/
void Course::calculateAverage(void) {
    float quizSums = 0;
    float hwSums = 0;
    float finalSums = 0;

    for(int i=0;i<mCurrentNumStudent;i++){
        float *q = mStudents[i].GetQuizScores();
        float *hw = mStudents[i].GetHwScores();
        float f = mStudents[i].GetFinalScore();

        for(int j=0;j<4;j++) quizSums = quizSums + *(q+j);
        for(int k=0;k<3;k++) hwSums = hwSums + *(hw+k);
        finalSums = finalSums + f;
    }

    cout<<"Quizzes-Avg: "<<quizSums/(4*mCurrentNumStudent)<<endl;
    cout<<"Homeworks-Avg: "<<hwSums/(3*mCurrentNumStudent)<<endl;
    cout<<"Final-Avg: "<<finalSums/mCurrentNumStudent<<endl;
}

/*
    Definition: Gets the student list inside the course object
    @Parameters: none
    @Return: Student list's pointer
*/
Student *Course::getStudentsList(){
    return mStudents;
}
