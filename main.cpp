#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define deb(x) cout << #x << " = " << x << endl;

string check_for_file(string loc) {
  for (const auto &entry : filesystem::directory_iterator(loc)) {
    string file_name = entry.path();
    string end_letters =
        file_name.substr(file_name.size() - 4, file_name.size());
    if (end_letters == "todo") {
      return file_name;
    }
  }

  return "0";
}


void create_todo()
{
    ofstream file("todo"); 
    file.close(); 
}

void get_data(string path, vector<string> &dataset) {
  ifstream input_file(path);
  if (input_file.is_open() == false) {
    cerr << "error opening and printing the file" << endl;
    return;
  }

  string line;
  while (getline(input_file, line)) {
    dataset.push_back(line);
  }

  input_file.close();
}

void add_task(vector<string> &data, string task) {
  string prefix = "[ ] ";
  prefix = prefix + task;
  data.push_back(prefix);
}

void delete_task(vector<string> &data, int pos) {
  data.erase(data.begin() + pos);
}

void print_dataset(vector<string> &data) {
  int i = 0;
  for (auto x : data) {
    cout << i << ". " << x << endl;
    i++;
  }
}

void checkmark(vector<string> &data, int pos) { data[pos][1] = '-'; }

void uncheckmark(vector<string> &data, int pos) { data[pos][1] = ' '; }

// update the dataset - checks for user for the removal or insertion or check
void update(vector<string> &data) {

  bool running = true;
  cout << "PRESS U TO ADD //  X TO CHECK // D TO DELETE // Q TO QUIT" << endl;

  print_dataset(data);

  while (running) {

    char access_code;
    cin >> access_code;

    switch (access_code) {

    case 'u': {
      string new_task;
      cout << "Enter the task :";
      cin.ignore();
      getline(cin, new_task);
      add_task(data, new_task);
      print_dataset(data);
      break;
    }

    case 'x': {
      int pos;
      cout << "Enter the number to check / complete : ";
      cin >> pos;
      char mark = data[pos][1]; 
      if(mark == '-')
      {
        uncheckmark(data,pos); 
      }else{
        checkmark(data,pos); 
      }
      print_dataset(data);
      break;
    }

    case 'd': {
      int pos;
      cout << "Enter the Number to delete : ";
      cin >> pos;
      delete_task(data, pos);
      print_dataset(data);
      break;
    }

    case 'q': {
      running = false;
      print_dataset(data);
      break;
    }

    default: {
      cout << "Enter valid key" << endl;
      break;
    }
    }
  }
}

int main(int argc,char *argv[]) {

  string loc  = std::filesystem::current_path(); 
    
  if(argc == 2)
  {
      loc = argv[1]; 
  }

  string file_loc = check_for_file(loc);

  if(file_loc == "0"){
    printf("THERE IS NO TODO FILE IN THE DIRECTORY GIVEN\n");  
    printf("CREATING THE TODO FILE"); 
    create_todo(); 
    return 0; 
  }

  vector<string> dataset;

  if (file_loc != "0") {
    get_data(file_loc, dataset);
  }
  // check if the todo file exist
  update(dataset);

  fstream file;
  file.open(file_loc, fstream::out | fstream::trunc);

  if (file.is_open()) {

    for (auto x : dataset) {
      file << x << endl;
    }

    file.close();
  }
  // update the file 1. clear the contents and rewrite with dataset

  return 0;
}
