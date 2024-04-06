#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#define IOS                     \
  ios_base::sync_with_stdio(0); \
  cin.tie(NULL);                \
  cout.tie(NULL);
using namespace std;
struct Question
{
    string quest = "", ans = "";
    int quest_id;
    int from, to;
    int ans_from, ans_to;
};
struct User
{
    int u_id;
    string name = "", email = "", password = "";
};
vector<User>dataa;
vector< Question>v;
class father
{
private:
    int from, to, q_id;
public:
    void set_q(int i)
    {
        q_id = i;
    }
    int get_qid()
    {
        return q_id;
    }
    void set_from(int i)
    {
        from = i;
    }
    void set_to(int i)
    {
        to = i;
    }
    int get_to()
    {
        return to;
    }
    int get_from()
    {
        return from;
    }
    //virtual void ask(string a);
};
class question : public father

{
private:
    string qu;
public:
    void ask(string a)
    {
        qu = a;
    }
    string get_qu()
    {
        return qu;
    }
};
class answer : public father

{
private:
    string ans;
public:
    void ask(string a)
    {
        ans = a;
    }
    string get_ans()
    {
        return ans;
    }
};
class data_base
{
public:
    void parallel()
    {
        v.clear();
        int id = 0, from = 0, to = 0;
        string s = "";
        Question temp;
        ifstream file("question.txt");
        while (file >> id >> from >> to)
        {
            file.ignore();
            getline(file, temp.quest);
            temp.quest_id = id;
            //cout << temp.quest << '\n';
            temp.from = from;
            temp.to = to;
            //temp.quest = s;
            v.push_back(temp);
        }
        file.close();
        ifstream fille("answer.txt");
        while (fille >> id >> from >> to)
        {
            fille.ignore();
            getline(fille, s);
            for (int i = 0; i < v.size(); i++)
            {
                if (id == v[i].quest_id)
                {
                    v[i].ans = s;
                    v[i].ans_from = from;
                    v[i].ans_to = to;
                    break;
                }
            }
        }
        fille.close();
        dataa.clear();
        //int id;
        string name, email, password;
        ifstream fiile("user.txt");
        while (fiile >> id >> name >> email >> password)
        {
            User user;
            user.u_id = id;
            user.email = email;
            user.name = name;
            user.password = password;
            dataa.push_back(user);
        }
        fiile.close();
    }
    void read_questions()
    {
        v.clear();
        int id = 0, from = 0, to = 0;
        string s = "";
        Question temp;
        ifstream file("question.txt");
        while (file >> id >> from >> to)
        {
            file.ignore();
            getline(file, temp.quest);
            temp.quest_id = id;
            //cout << temp.quest << '\n';
            temp.from = from;
            temp.to = to;
            //temp.quest = s;
            v.push_back(temp);
        }
        file.close();
    }
    void read_answer()
    {
        int id = 0, from = 0, to = 0;
        string s = "";
        ifstream fille("answer.txt");
        while (fille >> id >> from >> to)
        {
            fille.ignore();
            getline(fille, s);
            for (int i = 0; i < v.size(); i++)
            {
                if (id == v[i].quest_id)
                {
                    v[i].ans = s;
                    v[i].ans_from = from;
                    v[i].ans_to = to;
                    break;
                }
            }
        }
        fille.close();
    }
    void write_question()
    {
        //parallel();
        ofstream filee("Question.txt", ios::app);
        for (int i = 0; i < v.size(); i++)
        {
            filee << v[i].quest_id << '\n' << v[i].from << '\n' << v[i].to << '\n' << v[i].quest << '\n';
        }
        filee.close();
    }
    void write_answer()
    {
        //parallel();
        ofstream ffile("answer.txt", ios::app);
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].ans != "")
            {
                ffile << v[i].quest_id << '\n' << v[i].ans_from << '\n' << v[i].ans_to << '\n' << v[i].ans << '\n';
            }
        }
        ffile.close();
    }
    void read_users()
    {
        dataa.clear();
        int id;
        string name, email, password;
        ifstream fiile("user.txt");
        while (fiile >> id >> name >> email >> password)
        {
            User user;
            user.u_id = id;
            user.email = email;
            user.name = name;
            user.password = password;
            dataa.push_back(user);
        }
        fiile.close();
    }
    void write_users(User ob)
    {
        //parallel();
        ofstream file("user.txt", ios::app);
        file << ob.u_id << '\n' << ob.name << '\n' << ob.email << '\n' << ob.password << '\n';
        file.close();
    }
};
class services :public data_base
{
public:
    void delete_question(int my_id)
    {
        parallel();
        Question Quest;
        int id, from, to, temp, indx = 0;
        cout << "enter the question id you want to delete\n";
        cin >> temp;
        string s;
        v.clear();
        ifstream file("question.txt");
        bool ex = 0;
        while (file >> id >> from >> to)
        {
            file.ignore();
            getline(file, s);
            Quest.from = from;
            Quest.to = to;
            Quest.quest = s;
            Quest.quest_id = id;
            v.push_back(Quest);
            if (from == my_id && id == temp)
            {
                ex = 1;
                indx = v.size() - 1;
            }
        }
        file.close();
        read_answer();
        /////////////////////////////////
        if (!ex)
        {
            cout << "can not delete the question\n";
        }
        else
        {
            v.erase(v.begin() + indx);
            cout << "deleted successfully\n";
        }
        ofstream filee("question.txt", ios::trunc);
        filee.clear();
        for (int i = 0; i < v.size(); i++)
        {
            filee << v[i].quest_id << '\n' << v[i].from << '\n' << v[i].to << '\n' << v[i].quest << '\n';
        }
        filee.close();
        ofstream ffile("answer.txt", ios::trunc);
        ffile.clear();
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].ans != "")
            {
                ffile << v[i].quest_id << '\n' << v[i].ans_from << '\n' << v[i].ans_to << '\n' << v[i].ans << '\n';
            }
        }
        ffile.close();
    }
    void respond(int my_id)
    {
        parallel();
        //answer new_answer;
        Question new_question;
        cout << "enter question id you want to respond\n";
        int id; cin >> id;
        bool ex = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].quest_id == id)
            {
                if (v[i].from == my_id)
                {
                    ex = 0;
                    break;
                }
                else
                {
                    ex = 1;
                    break;
                }
            }
        }
        if (ex == 0)
        {
            cout << "can not answer\n";
            return;
        }
        //new_answer.(i);
        new_question.quest_id = id;
        //new_answer.set_from(my_id);
        new_question.ans_from = my_id;
        cout << "enter your answer\n";
        string s;
        cin.ignore();
        getline(cin, s);
        new_question.ans = s;
        //cout << new_question.ans << '\n';
        //new_answer.ask(s);
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].quest_id == new_question.quest_id)
            {
                new_question.ans_to = v[i].from;
                v[i].ans_from = new_question.ans_from;
                v[i].ans_to = new_question.ans_to;
                v[i].ans = new_question.ans;
                break;
            }
        }
        write_answer();
    }
    void ask(int my_id)
    {
        parallel();
        read_questions();
        //  cout << my_id << "\n";
        Question new_question;
        cout << "enter user id you want to ask\n";
        int i; cin >> i;
        if (i > dataa[dataa.size() - 1].u_id || i == my_id)
        {
            cout << "wrong id\n";
            return;
        }
        new_question.to = i;
        new_question.from = my_id;

        cout << "enter your question\n";
        string s;
        cin.ignore();
        getline(cin, s);
        // cin.ignore();
        new_question.quest = s;
        int qid = 1;

        if (v.size() > 0)
        {
            qid = v[v.size() - 1].quest_id + 1;
        }
        new_question.quest_id = qid;
        v.push_back(new_question);
        new_question.quest_id = qid;
        ofstream filee("Question.txt", ios::app);
        filee << new_question.quest_id << '\n' << new_question.from << '\n' << new_question.to << '\n' << new_question.quest << '\n';
        filee.close();
    }
    void display()
    {
        parallel();
        read_questions();
        read_answer();
        if (!v.size())
        {
            cout << "There is no questions\n";
            return;
        }
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].quest_id != 0)
            {
                //cout << v[i].ans << '\n';
                cout << v[i].quest_id << " (from: " << v[i].from << ") (to: " << v[i].to << ") " << v[i].quest << '\n';
                if (v[i].ans != "")
                {
                    cout << "(from: " << v[i].ans_from << ") (to: " << v[i].ans_to << ") " << v[i].ans << "\n\n";
                }
                else
                {
                    cout << "No answer\n\n";
                }
            }
        }
    }
    void questions_to_u(int my_id)
    {
        parallel();
        read_questions();
        read_answer();
        bool ex = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].to == my_id)
            {
                cout << v[i].to << '\n';
                cout << v[i].quest_id << " (from: " << v[i].from << ") (to: " << v[i].to << ") " << v[i].quest << '\n';
                if (v[i].ans != "") {
                    cout << "(from: " << v[i].ans_from << ") (to: " << v[i].ans_to << ") " << v[i].ans << "\n\n";
                }
                else
                {
                    cout << "No answer\n";
                }
                ex = 1;
            }
        }
        if (!ex)
        {
            cout << "you don't receive any questions\n";
            return;
        }
        // write_question();
        //write_answer();
    }
    void questions_from_u(int my_id)
    {
        parallel();
        read_questions();
        read_answer();
        bool ex = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].from == my_id)
            {
                cout << v[i].from << '\n';
                cout << v[i].quest_id << " (from: " << v[i].from << ") (to: " << v[i].to << ") " << v[i].quest << '\n';
                if (v[i].ans != "") {
                    cout << "(from: " << v[i].ans_from << ") (to: " << v[i].ans_to << ") " << v[i].ans << "\n\n";
                }
                ex = 1;
            }
        }
        if (!ex)
        {
            cout << "you didn't ask any questions\n";
            return;
        }
        //   write_question();
        //write_answer();
    }
    void list_users()
    {
        parallel();
        read_users();
        cout << dataa.size() << '\n';
        for (int i = 0; i < dataa.size(); i++)
        {
            cout << dataa[i].u_id << ' ' << dataa[i].name << endl;
        }
        // write_users();
    }
    int sign_up()
    {
        parallel();
        User ob;
        cout << "enter the user_name\n";
        string y;
        cin >> y;
        ob.name = y;
        //int i = ob.get_id();
        cout << "enter E_mail\n";
        ifstream em("user.txt");
        while (1)
        {
            string x;
            cin >> x;
            int id;
            bool ex = 0;
            string name, email, password;
            while (em >> id >> name >> email >> password)
            {
                // cout << "0\n";
                if (x == email)
                {
                    ex = 1;
                    break;
                }
            }
            if (ex)
            {
                cout << "This E_mail is taken choose another one\n";
                continue;
            }
            else
            {
                em.close();
                ob.email = x;
                break;
            }
        }
        cout << "enter password\n";
        string x;
        cin >> x;
        ob.password = x;
        int i = 1;
        read_users();
        if (dataa.size() > 0)
            i = ++dataa[dataa.size() - 1].u_id;
        ob.u_id = i;
        //  dataa.push_back(ob);
        write_users(ob);
        return i;
    }
    int sign_in()
    {
        parallel();
        read_users();
        cout << "enter your email\n";
        string y, name, email, password;
        cin >> y;
        int id = 0;
        bool exist = 0;
        //cout << dataa.size();
        for (int k = 0; k < 3; k++)
        {
            for (int j = 0; j < dataa.size(); j++)
            {
                if (y == dataa[j].email)
                {
                    exist = 1;
                    id = dataa[j].u_id;
                    break;

                }
            }
            if (exist)
            {
                break;
            }
            else
            {
                cout << "Invalid email,please try again\n";
                cin >> y;
            }
        }
        if (exist == 0)
        {
            sign_in_up();
        }
        cout << "enter your password\n";
        string z;
        cin >> z;
        bool ex = 0;
        for (int k = 1; k < 4; k++)
        {
            for (int i = 0; i < dataa.size(); i++)
            {
                if (id == dataa[i].u_id)
                {
                    if (z == dataa[i].password)
                    {
                        ex = 1;
                        break;
                    }
                }
            }
            if (ex)
            {
                break;
            }
            else
            {
                cout << "Wrong password\n";
                cin >> z;
            }
        }
        if (ex == 0)
        {
            sign_in_up();
        }
        return id;
    }
    int sign_in_up()
    {
        cout << "Enter : \n 1- Sign in\n 2- sign up\n";
        int x;
        while (1)
        {
            cin >> x;
            if (x == 1)
            {
                x = sign_in();
                break;
            }
            else if (x == 2)
            {
                x = sign_up();
                break;
            }
            else
            {
                cout << "wrong choise\n";
            }
        }
        return x;
    }
};
class user :public services
{
private:
    string password, email;
    int id;
    string name;
public:
    void set_id(int i)
    {
        id = i;
    }
    int get_id()
    {
        return id;
    }
    void set_name(string x)
    {
        name = x;
    }
    string get_name()
    {
        return name;
    }
    void set_pass(string x)
    {
        password = x;
    }
    string get_pass()
    {
        return password;
    }
    void set_email(string x)
    {
        email = x;
    }
    string get_email()
    {
        return email;
    }
};
void menu()
{
    cout << "\n 1- View questions forwarded to you\n";
    cout << " 2- View questions you asked\n";
    cout << " 3- Ask a questions\n";
    cout << " 4- Answer a question\n";
    cout << " 5- Delete question\n";
    cout << " 6- List all the users in the system\n";
    cout << " 7- See all questions and answers\n";
    cout << " 8- Log out\n";
}
int main()
{
    IOS;
    user new_user;
    services ob;
    //  ob.read_users();
    int w = new_user.sign_in_up();
    while (1)
    {
        menu();
        cout << "enter your choice\n";
        int choice = 0;
        cin >> choice;
        if (choice == 1)
        {
            new_user.questions_to_u(w);
        }
        else if (choice == 2)
        {
            new_user.questions_from_u(w);
        }
        else if (choice == 3)
        {

            new_user.ask(w);
        }
        else if (choice == 4)
        {
            new_user.respond(w);
        }
        else if (choice == 5)
        {
            new_user.delete_question(w);
        }
        else if (choice == 6)
        {
            //new_user.list_users();
            ob.list_users();
        }
        else if (choice == 7)
        {
            new_user.display();
        }
        else if (choice == 8)
        {
            w = new_user.sign_in_up();
        }
        else
        {
            cout << "wrong choice, please try again\n";
        }
    }
    return 0;
}