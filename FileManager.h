#include <iostream>
#include <string>
#include <vector>

//avoid using namespace std
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;

//모드 지정용 FileType
enum class FileType {
	File, Directory, All
};

class FileManager {
public:
	//User Interface

	FileManager() = delete; //기본 생성자는 없음(제거)
	FileManager(string dir_path); //생성자

	//Getter()
	int get_count(FileType ft) const;

	//print
	void print_list(FileType ft);
	void replace_name(FileType ft, string& find, string& replace); //오버로딩
	void insert_left_name(FileType ft, string& insert_str); //오버로딩
	void insert_right_name(FileType ft, string& insert_str); //오버로딩

private:
	//Encapsulation

	//경로 저장 값
	string dir_path;

	//파일 갯수, 디렉토리 갯수, 모든 파일 갯수
	int file_count, dir_count, all_count;

	//디렉토리의 파일, 폴더 목록들
	vector<string> file_list;
	vector<string> dir_list;

	//문자열 삽입, 치환 함수
	void replace_name(vector<string>& lst, string& find, string& replace);
	void insert_left_name(vector<string>& lst, string& insert_str);
	void insert_right_name(vector<string>& lst, string& insert_str);

	void insert_last_symbol(string& path);
	string ReplaceAll(string& str, const std::string& from, const std::string& to);
};