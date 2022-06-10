#include <iostream>
#include <string>
#include "FileManager.h"
#include <format>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::format;


//�ƽ�Ű ��Ʈ ��¿� ����
string ascii_art = "______  _  _         _____  _                                      \n|  ___|(_)| |       /  __ \\| |                                     \n| |_    _ | |  ___  | /  \\/| |__    __ _  _ __    __ _   ___  _ __ \n|  _|  | || | / _ \\ | |    | '_ \\  / _` || '_ \\  / _` | / _ \\| '__|\n| |    | || ||  __/ | \\__/\\| | | || (_| || | | || (_| ||  __/| |   \n\\_|    |_||_| \\___|  \\____/|_| |_| \\__,_||_| |_| \\__, | \\___||_|   \n                                                  __/ |            \n                                                 |___/\n";


void draw_border() {
	cout << "--------------------------------------------------------------------\n";
}

void draw_main()
{
	//ù ����ȭ�� ������ 
	draw_border();
	cout << ascii_art;
	cout << "���� �����̸� ����� v0.1" << endl;
	draw_border();
}



string get_file_path(string dialog)
{
	//��� �Է� ����� �ӽ� ����
	string temp;

	//�Է� ���̾�α� ���
	cout << dialog;

	//cin ���� ������ ������� �Է� ���� �� ����. getline �� ���� ������ �����ؼ� �о���.
	std::getline(cin, temp);

	draw_border();

	return temp;
}

int main(void) {
	setlocale(LC_ALL, ""); //�ѱ� ��� �б� ���� �������� �ش� ��ǻ�Ϳ� �ִ� �����Ϸ� �ٲ۴�. (�ʼ�)

	string dir_path = "";

	//ù ����ȭ�� ������ 
	draw_main();

	//��� �Է� �ޱ�
	dir_path = get_file_path("���� ��θ� �Է����ּ���. : ");

	//������ �ٷ�� ���� FileManager ��ü �����ϱ�
	FileManager fm(dir_path); //��ü ����

	if (fm.get_file_count() != 0) {
		fm.print_file_list(); //���� ����Ʈ ���
	}
	else {
		cout << "No Files in Directory...";
		return 0;
	}

	draw_border();

	string mode;

	do {
		cout << "�۾��Ͻ� ��带 �������ּ��� (p : ġȯ���, l : ���ʿ� ���ڿ� ����, r : �����ʿ� ���ڿ� ����, e : ����) : ";
		cin >> mode;
		cin.ignore(); //���� �Ѱ���ŭ �Է¹��� ����


		if (mode == "p") {
			string find, replace;
			cout << "ã�� ���ڿ��� �Է����ּ��� : ";
			getline(cin, find);

			cout << "ġȯ�� ���ڿ��� �Է����ּ��� : ";
			getline(cin, replace);

			string dialog;
			cout << format("�ش� ����� \"{}\" ���ڸ� ã�Ƽ� \"{}\" (��)�� ġȯ�ؼ� �̸��� �����մϴ�. \n���� �����Ͻðڽ��ϱ� ? (y/n) : ", find, replace);
			cin >> dialog;

			if (dialog == "y") {
				fm.replace_file_name(find, replace);
			}
			else {
				printf("����ڿ� ���� �۾��� ��ҵǾ����ϴ�.\n");
			}
		}
		else if (mode == "e") {
			cout << "����ڿ� ���� �۾��� ����Ǿ����ϴ�.";
		}
		else if (mode == "l") {
			string insert_str, dialog;
			cout << "������ ���ڿ��� �Է����ּ��� : ";
			getline(cin, insert_str);

			cout << format("�ش� ����� ���� �̸� �տ� \"{}\" �� ��� �����մϴ�. \n���� �����Ͻðڽ��ϱ� ? (y/n) : ", insert_str);
			cin >> dialog;

			if (dialog == "y") {
				fm.insert_left_file_name(insert_str);
			}
			else {
				printf("����ڿ� ���� �۾��� ��ҵǾ����ϴ�.\n");
			}
		}
		else if (mode == "r") {
			string insert_str, dialog;
			cout << "������ ���ڿ��� �Է����ּ��� : ";
			getline(cin, insert_str);

			cout << format("�ش� ����� ���� �̸� �ڿ� \"{}\" �� ��� �����մϴ�. \n���� �����Ͻðڽ��ϱ� ? (y/n) : ", insert_str);
			cin >> dialog;

			if (dialog == "y") {
				fm.insert_right_file_name(insert_str);
			}
			else {
				printf("����ڿ� ���� �۾��� ��ҵǾ����ϴ�.\n");
			}
		}
		else {
			printf("�ùٸ� ��尡 �ƴմϴ�.");
		}
	} while (mode != "e");

	getchar(); //���α׷� �ٷ� ������� �ʰ� �ϱ�
	return 0;
}