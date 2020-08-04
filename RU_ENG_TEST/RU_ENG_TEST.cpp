#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <iomanip>
using namespace std;
#define versia 1.41 
//Версия от 11.03

struct setup {

	int qwest;// Количество вопросов для теста

	int par;// количество пар слов в обучающем тесте (10,20)

	int forma_testa;// отношение теста (обучающий, рандомный, итоговый)
	int Podskazka; // Вывести пары слов и верные ответы? Да, нет
	int randomSet; // Заполнение рандомное? Да, нет

	int start_nomer;// номер стартового слова

	int signalerror;// звук на ошибках

}i_test, r_test, s_test, ex_test, per_test;

/*ТЕСТ*/
int TEST(int, int, setup);
/*Конструкции к тесту*/
void modul_slova(int);
int blok_ekzamena();
void stroka_perevod(int);
void pravila(setup, int);
string caps_registr(string);
string v_slova(int, int);

/*МЕНЮ*/
void privet();
int skill_menu(setup);
void bloc_menu20();
void bloc_menu10();

int getValue();
int itog_menu(setup);
void tema_menu();
void o_programme();
void show_slova(int, int);
void nastroika();

/****Констркуции к пользовательскому тесту*/
struct clovar {
	char clovo[24];
}name;
clovar *polzENG = 0;
clovar *polzRU = 0;
void polzovatel_test();
void napolnenie();
void savepolzTEST();

/***СЛОВА**/
string bloc_prost_rus(int);
string bloc_prost_eng(int);
string bloc_sush_rus(int);
string bloc_sush_eng(int);
string bloc_glagol_rus(int);
string bloc_glagol_eng(int);
string bloc_pril_rus(int);
string bloc_pril_eng(int);

int main()
{
	system("title (RET) - Russian-English Test v.1.42 ");
	system("mode con cols=80 lines=60");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");
	srand(time(0));
	// Структура {К-о вопросов, к-во пар, вид теста, подсказки, рандомное заполнение, первое слов, звуковой сигнал}	

	r_test = { 8, 10, 2, 1, 1, 1, 1 };
	s_test = { 15, 10, 0, 1, 0, 1, 1 };
	i_test = { 30, 100, 1, 0, 0, 0, 1 };
	ex_test = { 30, 400, 0, 0, 1, 1, 1 };
	per_test = { 10, 0, 0, 1, 0, 1, 1 };
	int x = 0;
	privet();
	do {
		system("cls");
		cout << "МЕНЮ: \n\n";
		cout << "1 - Случайный тесты: \n";
		cout << "2 - Обучающие тесты: \n";
		cout << "3 - Итоговые тесты: \n";
		cout << "4 - Пользовательский тест: \n";
		cout << "5 - Просмотр всех слов: \n";
		cout << "6 - О программе: \n";
		cout << "0 - НАСТРОЙКИ: \n";
		x = getValue();
		if (x == 1) {
			TEST(0, 0, r_test);
		}
		else if (x == 2) {
			skill_menu(s_test);
		}
		else if (x == 3) {
			itog_menu(i_test);
		}
		else if (x == 4) {
			polzovatel_test();
		}
		else if (x == 5) {
			tema_menu();
		}
		else if (x == 6) o_programme();
		else if (x == 0) {
			nastroika();
		}

	} while (1);
}


/***************************************************************************/
/***************************************************************************/
/***********************            ТЕСТ              **********************/
/***************************************************************************/
/***************************************************************************/

int TEST(int b_eng, int b_rus, setup test) {
	// Структура {К-о вопросов, к-во пар, вид теста, подсказки, рандомное заполнение, первое слов, звуковой сигнал}	
	//r_test = { 30, 20, 2, 1, 0, 0, 1 };
	//r_test = { 8, 10, 2, 1, 1, 1, 1 };
	int blok_the = b_eng;
	// Заполняем массивы словами
	string *pravoe_slovo = new string[test.par];
	string *levoe_slovo = new string[test.par];
	int *modul = new int[test.par]; // Для случайных тестов принимает принмает модуль принадлежности к группе

	string *otvets = new string[test.qwest]; // принмиает ответы
	string *prav = new string[test.qwest]; // принимает слова во время теста 
	string *left = new string[test.qwest]; // принимает слова во время теста 
	for (int i = 0, start = 0; i < test.qwest; i++) {
		otvets[i] = " - ";
		prav[i] = " - ";
		left[i] = " - ";
	}

	if (test.randomSet == 0) {
		for (int i = 0, start = test.start_nomer; i < test.par; i++, start++) {
			pravoe_slovo[i] = v_slova(b_rus, start);
			levoe_slovo[i] = v_slova(b_eng, start);
			modul[i] = b_eng;
		}
	}
	else {
		int rand_modul;
		if (b_rus == 0) rand_modul = 1;
		else rand_modul = 0;
		for (int i = 0, start = 0; i < test.par; i++) {
			if (rand_modul == 1) {
				b_eng = blok_ekzamena(); //выбор случайного блока
				b_rus = b_eng + 1;
			}
			start = rand() % 100 + 1;
			modul[i] = b_eng;
			pravoe_slovo[i] = v_slova(b_rus, start);
			levoe_slovo[i] = v_slova(b_eng, start);
		}
	}
	//cout << 3 << endl;
	pravila(test, blok_the);
	// показать словесные пары:
	if (test.Podskazka == 1) {
		system("cls");
		cout << "Запомните выведенные на экран пары слов: \n\n";
		for (int i = 0; i < test.par; i++) {
			//int tmp = modul[i];
			cout << setiosflags(ios::left);
			cout.width(11);
			modul_slova(modul[i]);
			cout << setiosflags(ios::right);
			cout.width(3);
			cout << i + test.start_nomer;
			cout.width(14);
			if (b_eng % 2 == 0 || modul[i] % 2 == 0) {
				cout << levoe_slovo[i];
				cout << " - " << pravoe_slovo[i] << endl;
			}
			else {
				cout << pravoe_slovo[i];
				cout << " - " << levoe_slovo[i] << endl;
			}
		}
		system("pause");
	}
	else {}

	// Тест
	int couterPlus = 0, close = test.qwest, couterFAIL = 0, endend = 1;
	do {
		system("cls");
		int i = rand() % test.par;
		cout << close << ". ";
		stroka_perevod(b_eng); // введите слово на ру или анг
		cout << levoe_slovo[i] << endl;
		if (test.forma_testa == 1 || test.forma_testa == 2) {
			modul_slova(modul[i]);
		}
		string clovo = "0";
		cin >> clovo;
		otvets[close - 1] = clovo;
		prav[close - 1] = caps_registr(pravoe_slovo[i]);
		left[close - 1] = levoe_slovo[i];
		// Проверка на правильность, с переоводом в капс
		if (caps_registr(clovo) == caps_registr("ENDTEST")) {
			endend = 0;
		}
		else if (caps_registr(clovo) == caps_registr(pravoe_slovo[i])) {
			cout << "ВЕРНО! \n";
			if (test.Podskazka == 1) cout << levoe_slovo[i] << " \t - \t " << pravoe_slovo[i] << endl;
			couterPlus++;
			system("pause");
			prav[close - 1] += "(+)";
		}
		else {
			if (test.signalerror == 1) cout << '\a';
			cout << "НЕ ВЕРНО! \n";
			if (test.Podskazka == 1) cout << levoe_slovo[i] << " \t - \t " << pravoe_slovo[i] << endl;
			couterFAIL++;
			system("pause");
			prav[close - 1] += "(-) ";
		}
		close--;
		cin.ignore(123232, '\n');
		//Завершить тест если закончились вопросы или тест прерван
		if (endend == 0 || close == 0) {
			system("cls");
			cout << "\tТЕСТ ЗАВЕРШЕН\n"
				"\nКоличество вопросов в блоке: " << test.qwest <<
				"\nВсего задано вопросов: " << couterPlus + couterFAIL <<
				"\nКоличество пар слов: " << test.par <<
				"\nКоличество правильных ответов: " << couterPlus <<
				"\nКоличество неправильных ответов: " << couterFAIL <<
				"\nТест пройден на " << couterPlus * 100 / test.qwest << " %\n";
			system("pause");
			//if (test.Podskazka == 0) {
			cout << endl << endl;
			cout << "СТАТИСТИКА:\n";
			cout << setw(3) << std::right << "№ " << setw(16) << std::right << "Ваш ответ  " << setw(16)
				<< "Верный ответ  " << setw(16) << std::right << "Вопрос     " << endl;
			for (int i = test.qwest - 1, a = 1; i >= 0; i--, a++) {
				cout << setw(3) << std::right << a << setw(16) << otvets[i] << setw(16)
					<< prav[i] << setw(16) << std::left << left[i] << endl;
			}
			system("pause");
			//}
			close = 0;
		}


	} while (close);
	delete[] pravoe_slovo;
	delete[] levoe_slovo;
	delete[] modul;
	return 0;
}

/***************************************************************************/
/***************************************************************************/
/********************        Дополнения к тесту          ********************/
/***************************************************************************/
/***************************************************************************/


int blok_ekzamena() {
	int x = rand() % 4 + 1;
	switch (x) {
	case 1:
		return 1; break;
	case 2:
		return 3; break;
	case 3:
		return 5; break;
	case 4:
		return 7; break;
	}
}

void modul_slova(int nomer_modul) {
	switch (nomer_modul) {
	case 1:
	case 2:
		cout << "Общее> ";
		break;
	case 3:
	case 4:
		cout << "Существ.-> ";
		break;
	case 5:
	case 6:
		cout << "Глагол-> ";
		break;
	case 7:
	case 8:
		cout << "Прилаг.-> ";
		break;
	case 9:
	case 10:
		cout << "Польз.-> ";
		break;
	default: cout << "со случайными частями речи! ";
	}
}

void stroka_perevod(int b_rus) {
	switch (b_rus) {
	case 1: case 3: case 5: case 7:
		cout << "Введите это слово на английском -> ";
		break;
	case 2: case 4: case 6: case 8:
		cout << "Введите это слово на русском -> ";
		break;
	}
}

void pravila(setup test, int b_eng) {
	system("cls");

	/*modul_slova(b_eng); // Определит группу*/

	cout << "Инструкция: \n\n";
	if (b_eng == 1 || b_eng == 2) cout << "- Тема теста: \"Простые общие слова\"\n";
	else if (b_eng == 3 || b_eng == 4) cout << "- Тема теста: \"Существительные\"\n";
	else if (b_eng == 5 || b_eng == 6) cout << "- Тема теста: \"Глаголы\"\n";
	else if (b_eng == 7 || b_eng == 8) cout << "- Тема теста: \"Прилагательные\"\n";
	else if (b_eng == 9 || b_eng == 10) cout << "- Тема теста: \"Пользовательский\"\n";
	else cout << "- Тема теста: \"Объединенная группа\"\n";
	cout << "- Количество вопросов в тесте: " << test.qwest << " вопросов!\n";
	cout << "- Количество вариантов вопросов: " << test.par << " RU-ENG пар слов \n";
	cout << "- В качестве  ответов  программа  принимает  только  перевод  указный в\n";
	cout << "обучающей программе.\n";
	cout << "В качестве  ответа  необходимо  вводить  только  ключевое  слово, текст\n"
		"в скобках является комментарием к переводу, его вводить не нужно!\n";
	if (test.Podskazka == 1) {
		cout << "- После каждого  ответа  вы  получить  информацию  о  верном  переводе.\n";
		cout << "- В конце теста вы ознакомится  со  статистикой  данных  Вами  ответов.\n";
	}
	else {
		cout << "- После  каждого  ответа  программа сообщит верный ли ответ был дан или\n";
		cout << "нет, но сами верные ответы будут указаны только  в  итоговой  статистке\n";
		cout << "по оканчанию теста.\n\n";
	}
	cout << "Для преждевременного завершения теста используйте стоп слово: ENDTEST\n\n";
	cout << "\t\t\t УДАЧИ!!!\n\n\n";
	system("pause");
}


string caps_registr(string slovo) {
	int len = slovo.size();
	string slovoplus;
	for (int i = 0; i < len&& slovo[i] != ' '; i++)
	{
		slovo[i] = toupper(slovo[i]);
		slovoplus += slovo[i];
	}
	return slovoplus;
}

void show_slova(int b_rus, int b_eng) {
	for (int i = 1; i <= 100; i++) {
		cout << setiosflags(ios::left);
		cout.width(3);
		cout << i;
		cout << setiosflags(ios::right);
		cout.width(20);
		cout << v_slova(b_eng, i);
		cout << " - " << v_slova(b_rus, i) << endl;
	}
	system("pause");
}

string v_slova(int bloc, int nomer) {
	//Номер слова, номер блока из 8, 

	char s1[24];
	string str;
	switch (bloc) {
	case 1: return bloc_prost_rus(nomer); break;
	case 2:	return bloc_prost_eng(nomer); break;
	case 3:	return bloc_sush_rus(nomer); break;
	case 4:	return bloc_sush_eng(nomer); break;
	case 5:	return bloc_glagol_rus(nomer); break;
	case 6:	return bloc_glagol_eng(nomer); break;
	case 7:	return bloc_pril_rus(nomer); break;
	case 8:	return bloc_pril_eng(nomer); break;
	case 9:
		nomer--;
		strcpy_s(s1, polzENG[nomer].clovo);
		str = string(s1);
		return str;
		break;
	case 10:
		nomer--;
		strcpy_s(s1, polzRU[nomer].clovo);
		str = string(s1);
		return str;
		break;
	}
}


/***************************************************************************/
/***************************************************************************/
/************************         МЕНЮ         *****************************/
/***************************************************************************/
/***************************************************************************/

void privet() {
	cout <<
		"О программе: RET_400 (Russian - English Test) v." << versia << "\n\n"
		"Согласно некой концепции, блуждающей в сети,  в английском языке есть 400\n"
		"основных слов из которых состоит  70%  английских текстов.  Согласно этой\n"
		"концепции,  знание  этих слов позволит понимать большую часть английского\n"
		"текста, а также изложить любую мысль на английском языке.\n"
		"RET_400 (Russian - English Test) – это обучающая программа, целью которой\n"
		"является помочь  пользователю  расширить  свой  словарный  запас  на  эти\n"
		"400 английских слова.  \n\n"

		"Данная программа может быть использована  как  дополнительный  инструмент\n"
		"при изучении английского языка. \n\n"
		"P.S.:  Для  получения  начального  (A — Elementary)  —  уровня  требуется\n"
		"словарный запас в 1500 слов. \n \n";

	system("pause");
}

void o_programme() {
	system("cls");
	cout <<
		"О программе: RET_400 (Russian - English Test) v." << versia << "\n\n"
		"Согласно некой концепции, блуждающей в сети,  в английском языке есть 400\n"
		"основных слов из которых состоит  70%  английских текстов.  Согласно этой\n"
		"концепции,  знание  этих слов позволит понимать большую часть английского\n"
		"текста, а также изложить любую мысль на английском языке.\n"
		"RET_400 (Russian - English Test) – это обучающая программа, целью которой\n"
		"является помочь  пользователю  расширить  свой  словарный  запас  на  эти\n"
		"400 английских слова.  \n\n"

		"Данная программа может быть использована  как  дополнительный  инструмент\n"
		"при изучении английского языка. \n\n"
		"P.S.:  Для получения начального  (A  —  Elementary)  —  уровня  требуется\n"
		"словарный запас в 1500 слов. \n\n"


		"Концепция программы: \n"
		"Предоставить пользователю возможность  расширить  свой словарный запас на\n"
		"400 английских слов с помощью обучающих тестов.\n\n"

		"Что реализовано в программе: \n"
		"- Возможность проходит обучающие тесты, разделенные на  блоки  по  темам;\n"
		"- Возможность проходит случайно собранный тест из разных блоков; \n"
		"- Возможность проходить итоговый тест, без подсказки вначале; \n"
		"- Возможность загружать свои собственные тесты;\n"
		"- Выводимые на консоль пары слов выровнены по центральной линии; \n"
		"- Тесты могут принимать не только английские слова, но и русские;\n"
		"- При вводе ответа в консоль, пользователь не зависит от регистра; \n"
		"- Пользователь может изменять настройки программы; \n \n";
	system("pause");
	system("cls");
	cout <<
		"Доступные виды тестов: \n"
		"1. Случайный тест: Тест, случайно сгенерированный из доступных в обучающей\n"
		"программе пар слов.  Перед тестом пользователю предоставляется возможность\n"
		"ознакомиться с парами слов, которые будут использованы в запущенном тесте.\n"
		"При ответе на вопрос программа так же сообщает верный перевод.\n\n"

		"2. Обучающие тесты:  Тесты  обучающей  программы  разделен  на  4  группы:\n"
		"Простые повседневные слова,  Существительные,  Глаголы  и  Прилагательные.\n"
		"В каждом обучающем блоке по  100 слов, для удобства заучивания слов каждая\n"
		"группа разбита на блоки по  10  слов. Пользователь  через настройки  может\n"
		"изменить обучающую программу, увеличив количество слов в блоке с 10 до 20.\n"
		"Перед  тестом   пользователю  предоставляется  возможность  ознакомиться с\n"
		"парами слов, которые будут использованы в запущенном тесте.  При ответе на\n"
		"вопрос программа так же сообщает верный перевод.\n\n"

		"3. Итоговые тесты: тесты для оценки знаний одной из изучаемых групп.Перед\n"
		"тестом   нет  подсказки  о  парах  слов,   которые  будут  использованы в\n"
		"запущенном тесте. При ответе на вопрос верный перевод не сообщается.\n\n"

		"4. Экзаменационный тест:  финальный тест, включает в себя  все  400  слов\n"
		"обучающей программы.  Перед  тестом нет подсказки о парах  слов,  которые\n"
		"будут использованы в запущенном тесте.При ответе на вопрос верный перевод\n"
		"не сообщается.\n\n"

		"5. Пользовательский тест: Тест, составленный из пар новых слов, внесенных\n"
		"пользователем.  Перед  тестом  пользователю  предоставляется  возможность\n"
		"ознакомиться с  парами  слов,   которые  будут  использованы в запущенном\n"
		"тесте. При ответе на вопрос программа так же сообщает верный перевод.\n\n";

	system("pause");
	system("cls");
	cout <<
		"ТЕКУЩЕЙ РЕЛИЗ:\n"
		"v.1.41 (11.03.2020)\n"
		"- Дополнен текст инструкции для пользовательского теста;\n"
		"- Исправлена ошибка нумерации вопросов в пользовательском тесте;\n"
		"- Исправлена ошибка, связанная с вылета программы при попытке загрузить в текстовые файлы не равное количество слов;\n"
		"- В итоговой статистике прохождения теста добавлена отметка о верных и не верных ответах;\n\n"

		"ПРЕДЫДУЩИЕ РЕЛИЗЫ:	\n"
		"v.1.40 (09.03.2020)\n"
		"- Добавлен новый вид теста «Пользовательский тест» - Тест который составляется из пары слов, заданных пользователем;\n"
		"- При заполнении пользовательского теста, текстовые файлы в которые сохраняются слова открываются автоматически;\n"
		"- В программе реализована возможность сохранить пары слов, заданные пользователем, для использования их при следующем включении программы, а также стереть их из программы;\n\n"

		"v.1.33 (05.03.2020)\n"
		"- Исправлена ошибка, связанная с завершением теста при вводе слов, оканчивающихся на букву \"t\"\n"
		"- Изменен метод принимаемых в качестве ответа слов.В качестве ответа принимается только одно слово.В обучающей программе слова требующие более детальный перевод сообщается в виде ключевого слова с комментарием в круглых скобках;\n\n"

		"v.1.32 (03.03.2020) \n"
		"- Изменено меню настроек(Настройки теперь размещены в отдельной функции);\n"
		"- В текст инструкции добавлена дополнительная информация о тесте;\n"
		"- Добавлена нумерация вопросов при прохождении теста;\n\n"

		"v.1.31 (02.03.2020) \n"
		"- Исправлена ошибка, связанная с вылетом программы,  когда  в  настройках\n"
		"установлено меньше вопросов чем доступных пар слов;\n\n"

		"v.1.30 (01.03.2020) \n"
		"- Для корректного взаимодействия пользователя с меню установлена  система\n"
		"защиты от дурака (предотвращает  ввод  нескольких  команд  или  команд  с\n"
		"неверными символами);\n"
		"- Информация о программе и Лого выравнены по ширине;\n"
		"- Изменено отображение инструкции (теперь оно аккуратное и информативное)\n"
		"- В Тест добавлено стоп слово : EndTest;\n"
		"- Из итоговых и экзаменационных тестов убраны  подсказки  вначале  теста,\n"
		"а также подсказки, всплывающие во время теста;\n"
		"- По окончанию итоговых  тестов  можно  ознакомится  со  всеми  заданными\n"
		"вопросами и увидеть верный ответ;\n"
		"- Построено меню для пользовательского теста, и  предварительная  функция\n"
		"приема текста;\n\n "

		"v.1.22 (24.02.2020) \n"
		"- В блок с обучающими тестами добавлен тест со случайным блоком\n"
		"- Изменено меню настроек; \n\n "

		"v.1.21 (23.02.2020) \n"
		"- Для «случайного обучающего теста» и «Экзаменационного теста»  добавлено\n"
		"добавлено обозначение, принадлежности слова к части речи; \n \n"

		"v.1.20 (22.02.2020) \n"
		"- настройки для тестов, а также некоторые другие  значения,  передаваемые\n"
		"в тест и между функциями, реализованы ввиду структуры\n"
		"-добавлен новый  вариант  теста  –  «случайный  обучающий  тест»  -  этот\n"
		"тест показать все пары слов, которые будут в этом тесте\n"
		"- основная функция с тестом переписана, теперь она принимает слова в свои\n"
		"собственные динамические массивы, а не взывает каждое слово напрямую;\n\n"

		"v.1.11 (14.02.2020) \n"
		"- Функции с выбором блоков для 10 и 20 пар объединены вместе  логическими\n"
		"конструкциями, \n"
		"- Исправлены некоторые грамматические ошибки, \n"
		"- Изменена ветка меню (убраны лишние шаги на пати к тесту); \n\n"

		"v.1.10 (09.02.2020) \n"
		"- Решена проблема нечитаемых символов при вводе кириллицы, \n"
		"- Добавлена возможность настраивать количество вопросов в тестах, \n"
		"- Добавлена возможность изменить количество пар в тестов (10 и 20), \n"
		"- Выводимые на консоль пары слов выровнены по центральной линии, \n"
		"- Исправлена ошибка с крахом программы при выборе несуществующего меню, \n"
		"- Добавлено лого приветствия, перед тестом и сведения о программе, \n\n"
		"- Добавлено лого инструкции, перед началом теста; \n\n"

		"v.1.01 (01.02.2020) \n"
		"- Реализовано полное меню, \n"
		"- Добавлены все 400 слов программу, \n"
		"- Прописан разный сценарий для итогового и обучающего теста; \n\n"

		"v.1.00 (29.01.2020) \n"
		"- Основная часть программы (меню,  тест, 100 пар слов); \n\n";

	system("pause");
}

int skill_menu(setup test) {
	system("cls");
	cout << "МЕНЮ: \n\n";
	cout << "Тренировка по переводу с русского на английский\n\n"
		"\t 1 - Сто простых слов\n"
		"\t 2 - Сто существительных\n"
		"\t 3 - Сто глаголов\n"
		"\t 4 - Сто прилагательных\n\n"
		"Тренировка по переводу с английского на русский\n\n"
		"\t 5 - Сто простых слов\n"
		"\t 6 - Сто существительных\n"
		"\t 7 - Сто глаголов\n"
		"\t 8 - Сто прилагательных\n\n"
		"\t 9 - Случайны блок\n\n"
		"\t 0 - НАЗАД: \n";
	int x = getValue();
	if (x < 0 && x >10)
	{
		cout << "Такого варината нет\n";
		system("pause");
	}
	else if (x == 9) {
		int nechet, chetl;
		if (test.par == 10) test.start_nomer = 1 + (rand() % 10 * 10);
		else test.start_nomer = 1 + (rand() % 5 * 20);
		chetl = (((rand() % 8 + 1) / 2) * 2);
		nechet = chetl - 1;
		TEST(nechet, chetl, test);
	}
	else if (x > 0 && x < 10) {

		system("cls");

		if (test.par == 10) bloc_menu10();
		else bloc_menu20(); /*if (test.par = 20)*/

		int y = getValue();
		if (test.par == 20 && y != 1) y = (y*y) - 1;
		else y = y;

		switch (y) {
		case (1):	test.start_nomer = 1;	break;
		case (2):	test.start_nomer = 11; 	break;
		case (3):	test.start_nomer = 21;	break;
		case (4):	test.start_nomer = 31;	break;
		case (5):	test.start_nomer = 41;	break;
		case (6):	test.start_nomer = 51;	break;
		case (7):	test.start_nomer = 61;	break;
		case (8):	test.start_nomer = 71;	break;
		case (9):	test.start_nomer = 81;	break;
		case (10):  test.start_nomer = 91;	break;
		default:
			if (y != 0) {
				cout << "Такого варината нет\n";
				system("pause");
			}
		}
		if (y < 11 && y > 0) {
			switch (x) {
			case (1):
				TEST(1, 2, test);
				break;
			case (2):
				TEST(3, 4, test);
				break;
			case (3):
				TEST(5, 6, test);
				break;
			case (4):
				TEST(7, 8, test);
				break;
			case (5):
				TEST(2, 1, test);
				break;
			case (6):
				TEST(4, 3, test);
				break;
			case (7):
				TEST(6, 5, test);
				break;
			case (8):
				TEST(8, 7, test);
				break;
			default:
				cout << "Такого варината нет!\n";
				system("pause");
			}
		}
	}
	//skill_menu(test);
	return 0;
}


void bloc_menu10() {
	system("cls");
	cout << "МЕНЮ: \n\n";
	cout << "Выберите блок: \n";
	cout << "1  - БЛОК 1: от 1 до 10 слова\n";
	cout << "2  - БЛОК 2: от 11 до 20 слова \n";
	cout << "3  - БЛОК 3: от 21 до 30 слова \n";
	cout << "4  - БЛОК 4: от 31 до 40 слова \n";
	cout << "5  - БЛОК 5: от 41 до 50 слова \n";
	cout << "6  - БЛОК 6: от 51 до 60 слова \n";
	cout << "7  - БЛОК 7: от 61 до 70 слова \n";
	cout << "8  - БЛОК 8: от 71 до 80 слова \n";
	cout << "9  - БЛОК 9: от 81 до 90 слова \n";
	cout << "10 - БЛОК 10: от 91 до 100 слова \n";
	cout << "0  - НАЗАД: \n";
}

void bloc_menu20() {
	system("cls");
	cout << "МЕНЮ: \n\n";
	cout << "Выберите блок: \n";
	cout << "1  - БЛОК 1: от 1 до 20 слова\n";
	cout << "2  - БЛОК 2: от 21 до 40 слова \n";
	cout << "3  - БЛОК 3: от 41 до 60 слова \n";
	cout << "4  - БЛОК 4: от 61 до 80 слова \n";
	cout << "5  - БЛОК 5: от 81 до 100 слова \n";
	cout << "0  - НАЗАД: \n";
}


/**************************************/
/**************************************/

int itog_menu(setup test) {
	system("cls");
	cout << "МЕНЮ: \n\n";
	cout << "1 - Итоговый тест по блоку простых слов: \n";
	cout << "2 - Итоговый тест по блоку существительных: \n";
	cout << "3 - Итоговый тест по блоку глаголов: \n";
	cout << "4 - Итоговый тест по блоку прилагательных: \n\n";
	cout << "5 - ЭКЗАМЕНАЦИОННЫЙ ТЕСТ: \n\n";
	cout << "0 - НАЗАД: \n";
	int x = getValue();
	system("cls");
	switch (x) {
	case (1):
		TEST(1, 2, test);
		break;
	case (2):
		TEST(3, 4, test);
		break;
	case (3):
		TEST(5, 6, test);
		break;
	case (4):
		TEST(7, 8, test);
		break;
	case (5):
		TEST(0, 0, ex_test);
	}
	return 0;
}

int getValue()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
	{
		int a;
		cin >> a;
		// Проверка на предыдущее извлечение
		if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(123232, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Неверная команда попробуйте еще раз.\n";
			return -1;
		}
		else {
			std::cin.ignore(12, '\n'); // удаляем лишние значения
			return a;
		}
	}
}




/**************************************/
/**************************************/

void tema_menu() {
	system("cls");
	cout << "МЕНЮ: \n";
	cout << "1 - Показать 100 простых слов: \n";
	cout << "2 - Показать 100 существительных: \n";
	cout << "3 - Показать 100 глаголов: \n";
	cout << "4 - Показать 100 прилагательных: \n";
	cout << "0 - НАЗАД: \n";
	int x = getValue();
	system("cls");
	switch (x) {
	case 1:
		cout.width(15);
		cout << "100 простых слов: \n\n";
		show_slova(1, 2); break;
	case 2:
		cout.width(15);
		cout << "100 существительных: \n\n";
		show_slova(3, 4); break;
	case 3:
		cout.width(15);
		cout << "100 глаголов: \n\n";
		show_slova(5, 6); break;

	case 4:
		cout.width(15);
		cout << "100 прилагательных: \n\n";
		show_slova(7, 8); break;
	}
}



/*******************************************************************************/
/*******************************************************************************/
/**********************       Пользовательский      ****************************/
/**********************                             ****************************/
/**********************             ТЕСТ            ****************************/
/*******************************************************************************/
/*******************************************************************************/

void polzovatel_test() {
	/****ШАГ1 - ПРОВЕРКА СОХРАНЕНЕНИЯ****/
	if (per_test.forma_testa != 10) {
		_mkdir("RET_system");
		_chdir("RET_system");
		FILE *f1, *f2;
		int a = fopen_s(&f1, "Engsystem.txt", "r");
		int b = fopen_s(&f2, "RUsystem.txt", "r");
		if (a == 0 && b == 0) {
			per_test.forma_testa = 11; // дайм найстройку на запаолнение					
			fclose(f1);
			fclose(f2);
		}
		_chdir("../");
		napolnenie();
		per_test.forma_testa = 10; // отключаем заполнение в последующих запусках

	}
	else {
		per_test.forma_testa = 10; // отключаем заполнение в последующих запусках		
	}
	system("cls");
	/******   НАЧАЛО МЕНЮ   ********/
	/*ШАГ2 : Проводим проврку есть слова в масиивах или нет,
	если слов нет, игноируем меню и сразу переходим в к окну
	загруки слов в масиивы*/
	if (per_test.par > 0) {
		cout << "Меню пользовательского теста:\n\n"
			"1 - Запустить тест\n"
			"2 - Добавать слова в словарь\n"
			"3 - Сохранить словарь\n"
			"4 - Очистить словарь полностью\n"
			"5 - Показать словесные пары\n"
			"0 - НАЗАД\n\n"
			"Пользовательский тест  –  тест,  составленный  из  слов  пользователя.\n"
			"Что бы пополнить словарь следуйте инструкциями соответствующего  меню.\n"
			"Количество слов в словаре на данный момент: " << per_test.par << " \n\n";

		int vvodX = getValue();
		if (vvodX == 1) {
			TEST(9, 10, per_test);
		}
		else if (vvodX == 2) {
			napolnenie();
		}
		else if (vvodX == 3) {/* "3-Сохранить словарь\n"*/
			savepolzTEST();
		}
		else if (vvodX == 4) {  /* - 4-Очистить словарь полностью*/
			per_test.par = 0;
			delete[] polzRU;
			delete[] polzENG;
			int val = _chdir("RET_system");
			cout << val;
			system("pause");
			remove("Engsystem.txt");
			remove("RUsystem.txt");
			if (val == 0) _chdir("../");
		}
		else if (vvodX == 5) {
			for (int i = 0; i < per_test.par; i++) {
				cout.width(3);
				cout << i + 1;
				cout.width(20);
				cout << polzENG[i].clovo;
				cout << " - " << polzRU[i].clovo << endl;
			}
			system("pause");
		}
	}
	else {
		napolnenie();

	}
}

void savepolzTEST() {
	_mkdir("RET_system");
	int answer = _chdir("RET_system");
	//Если удалось войти в папку выполняю программу
	if (answer == 0) {
		FILE* f1, *f2;
		fopen_s(&f1, "Engsystem.txt", "w");
		fopen_s(&f2, "RUsystem.txt", "w");
		cout << "Сл";
		if (!f1 && !f2) { cout << "Сreg"; }
		else {
			cout << "Сл";
			for (int i = 0; i < per_test.par; i++) {
				fprintf(f1, "%s\n", polzENG[i].clovo);
				fprintf(f2, "%s\n", polzRU[i].clovo);
			}
		}
		fclose(f1);
		fclose(f2);
	}
	_chdir("../");
	cout << "Словарь успещно сохранен в файл!\n\n";
}

void napolnenie() {
	system("cls");
	//Создаю папку
	_mkdir("RET_system");
	int answer = _chdir("RET_system");
	//Если удалось войти в папку выполняю программу
	if (answer == 0) {
		FILE* f1, *f2;
		if (per_test.forma_testa == 11) {
			//Если в проверке меню выше вскрылось наличие сохранения
			fopen_s(&f1, "Engsystem.txt", "r");
			fopen_s(&f2, "RUsystem.txt", "r");
		}
		else {
			fopen_s(&f1, "Eng.txt", "w");
			fopen_s(&f2, "RU.txt", "w");
			fclose(f1);
			fclose(f2);
			/*Закрываю файлы программно что бы к ним иметь доступ из вне*/
			cout <<
				"Внимание инструкция : \n"
				"ШАГ1: Нажмите Enter в программе.\n"
				"ШАГ2: В первый  открывавшийся  текстовый  файл с  названием  (ENG.txt)\n"
				"вставите английские слова.  Слова должный идти в столбик, каждое слово\n"
				"должно начинается с новой строки.\n"
				"ШАГ3: Сохраните документ и закройте его.\n"
				"ШАГ4:  После  того  как  вы  закроете  первый  текстовый  файл,  сразу\n"
				"откроется второй с  названием  (RU.txt). Поместите в него перевод слов\n"
				"в том же порядке, в котором были  добавлены  английские  слова.  Слова\n"
				"должный идти в столбик, каждое слово должно начинается с новой строки.\n"
				"\n\n";

			system("pause");
			system("Eng.txt");
			system("RU.txt");
			system("pause");
			fopen_s(&f1, "RU.txt", "r");
			fopen_s(&f2, "Eng.txt", "r");
		}
		if (!f1 && !f2) {}
		else {
			int count = 0;
			while (!feof(f1) && !feof(f2)) {
				char buff[24] = {};
				char buff2[24] = {};
				if (fscanf_s(f1, "%s", buff, 24) &&
					fscanf_s(f2, "%s", buff2, 24))
					/*	if ((fgets(buff, 24, f1)) && (fgets(buff2, 24, f2)))*/
					count++;
			}
			//Читать файл с начала
			fseek(f1, 0, SEEK_SET);
			fseek(f2, 0, SEEK_SET);
			int size = per_test.par;
			per_test.par = per_test.par + count;
			clovar *TpolzENG = new clovar[per_test.par];
			clovar *TpolzRU = new clovar[per_test.par];
			// заполняю словорь с прошлого массива
			for (int i = 0; i < size; i++) {
				TpolzENG[i] = polzENG[i];
				TpolzRU[i] = polzRU[i];
			}
			//хаполняю словарь новыми словами из блокнота
			while (!feof(f1) && !feof(f2)) {
				if (fscanf_s(f1, "%s", TpolzENG[size].clovo, 24) &&
					fscanf_s(f2, "%s", TpolzRU[size].clovo, 24))
					/*if ((fgets(TpolzENG[size].clovo, 24, f1)) && fgets(TpolzRU[size].clovo, 24, f2))*/
					size++;
			}
			polzRU = TpolzRU;
			polzENG = TpolzENG;
			//???Удаление ненужных массивов крашит программу, ПОЧЕМУ???
			/*delete[] TpolzRU;
			delete[] TpolzENG;*/
		}
		fclose(f1);
		fclose(f2);
	}
	_chdir("../");
}

/****************************************************************************************
*****************************************************************************************
*****************************************************************************************
*****************************************************************************************
*****************************************************************************************
*****************************************************************************************/







void nastroika() {
	// Структура {К-о вопросов, к-во пар, вид теста, подсказки, рандомное заполнение, первое слов, звуковой сигнал}	
	system("cls");
	cout << " : НАСТРОЙКИ :\n\n";
	cout << " : ОБЩАЯ НАСТРОЙКА :\n";
	cout << "1 - Звуковой сигнал при ошибках:\n\n";

	cout << " : НАСТРОЙКА СЛУЧАЙНОГО ТЕСТА :\n";
	cout << "2 - Количество вопросов для случайного теста: \n";
	cout << "3 - Количество пар слов для случайного теста: \n\n";

	cout << " : НАСТРОЙКА ТЕСТОВ ОБУЧАЮЩЕЙ ПРОГРАММЫ :\n";
	cout << "4 - Количество вопросов для обучающих тестов: \n";
	cout << "5 - Количество пар слов для обучающих тестов: \n\n";

	cout << " : НАСТРОЙКА ЭКЗАМЕНАЦИОННЫХ ТЕСТОВ :\n";
	cout << "6 - Количество вопросов для итоговых тестов: \n\n";

	cout << "0 - НАЗАД: \n";
	int z = getValue();
	system("cls");
	if (z == 1) {
		cout << "Настройка звука: ";
		if (s_test.signalerror == 1) 	cout << "сейчас звук включен:\n";
		else cout << "сейчас звук выключен:\n";
		cout << "1-Включить звук\n";
		cout << "0-ВЫключить звук\n";
		z = getValue();
		if (z == 1) {
			s_test.signalerror = 1;
			r_test.signalerror = 1;
			i_test.signalerror = 1;
			ex_test.signalerror = 1;
			per_test.signalerror = 1;
			cout << "Вы включили звук:\n";
		}
		else if (z == 0) {
			s_test.signalerror = 0;
			r_test.signalerror = 0;
			i_test.signalerror = 0;
			ex_test.signalerror = 0;
			per_test.signalerror = 0;
			cout << "Вы выключили звук:\n";
		}
		else {
			cout << "Неверная команда\n\n";
		}
	}
	else if (z == 2) {
		cout << "Укажите количество вопросов для случайного теста:\n\n"
			"Сечас вопросов: " << r_test.qwest << endl;
		r_test.qwest = getValue();
		cout << "Установленно впоросов: " << r_test.qwest << endl;
	}
	else if (z == 3) {
		cout << "Укажите количество пар для случайного теста:\n";
		cout << "Сейчас пар: " << r_test.par << endl;
		r_test.par = getValue();
		cout << "Установленно пар" << r_test.par << endl;

	}
	else if (z == 4) {
		cout << "Укажите количество вопросов для обучающего теста:\n"
			"Сечас вопросов: " << s_test.qwest << endl;
		s_test.qwest = getValue();
		cout << "Установленно впоросов: " << s_test.qwest << endl;
	}
	else if (z == 5) {
		cout << "Укажите количество пар для обучающего теста:\n"
			"   1 - По 10 пар\n"
			"   2 - По 20 пар\n\n";
		cout << "Сейчас пар: " << s_test.par << endl;
		int par;
		cin >> par;
		if (par == 1) s_test.par = 10;
		else if (par == 2)s_test.par = 20;
		else cout << "Неверная команда";
		cout << "Установленно пар" << s_test.par << endl;

	}
	else if (z == 6) {
		cout << "Укажите количество вопросов для итогового теста:\n"
			"Сечас вопросов: " << i_test.qwest << endl;
		cin >> i_test.qwest;
		cout << "Установленно впоросов: " << i_test.qwest << endl;
	}
	else cout << "Возврат в меню:\n";
	system("pause");

}

/***************************************************************************/
/***************************************************************************/
/*************************       СЛОВА          ****************************/
/***************************************************************************/
/***************************************************************************/

string bloc_prost_rus(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "артикль (определённый артикль)"; break;
	case(2): clovo = "быть"; break;
	case(3): clovo = "к"; break;
	case(4): clovo = "в (из-за, о)"; break;
	case(5): clovo = "и"; break;
	case(6): clovo = "артикль  (неопределённый артикль, при сущ.\n     начинающемся на согласный звку)"; break;
	case(7): clovo = "в"; break;
	case(8): clovo = "что (который)"; break;
	case(9): clovo = "иметь"; break;
	case(10): clovo = "я"; break;
	case(11): clovo = "это (он, оно, это)"; break;
	case(12): clovo = "для"; break;
	case(13): clovo = "не"; break;
	case(14): clovo = "на"; break;
	case(15): clovo = "с"; break;
	case(16): clovo = "он"; break;
	case(17): clovo = "как (как, поскольку)"; break;
	case(18): clovo = "вы"; break;
	case(19): clovo = "делать"; break;
	case(20): clovo = "около (у,около,на)"; break;
	case(21): clovo = "этот"; break;
	case(22): clovo = "но"; break;
	case(23): clovo = "его"; break;
	case(24): clovo = "у (у, под, силами чего-либа)"; break;
	case(25): clovo = "от (от, из, с, у, по, изо)"; break;
	case(26): clovo = "они"; break;
	case(27): clovo = "мы"; break;
	case(28): clovo = "говорить"; break;
	case(29): clovo = "её"; break;
	case(30): clovo = "она"; break;
	case(31): clovo = "или"; break;
	case(32): clovo = "артикль (неопределённый артикль, для сущ.\n    начинающегося с гласного звука)"; break;
	case(33): clovo = "хотеть (проявлять волю)"; break;
	case(34): clovo = "мой"; break;
	case(35): clovo = "один"; break;
	case(36): clovo = "все"; break;
	case(37): clovo = "вероятность (модальный глагол, выражающий\n     желание, вероятность)"; break;
	case(38): clovo = "там"; break;
	case(39): clovo = "их"; break;
	case(40): clovo = "что"; break;
	case(41): clovo = "так"; break;
	case(42): clovo = "вверх"; break;
	case(43): clovo = "наружу"; break;
	case(44): clovo = "если"; break;
	case(45): clovo = "о"; break;
	case(46): clovo = "кто"; break;
	case(47): clovo = "получить"; break;
	case(48): clovo = "который"; break;
	case(49): clovo = "идти"; break;
	case(50): clovo = "мне"; break;
	case(51): clovo = "когда"; break;
	case(52): clovo = "делать"; break;
	case(53): clovo = "мочь"; break;
	case(54): clovo = "нравится"; break;
	case(55): clovo = "время"; break;
	case(56): clovo = "нет"; break;
	case(57): clovo = "точно (правильный)"; break;
	case(58): clovo = "ему"; break;
	case(59): clovo = "знать"; break;
	case(60): clovo = "брать"; break;
	case(61): clovo = "люди"; break;
	case(62): clovo = "внутрь (предлог в)"; break;
	case(63): clovo = "год"; break;
	case(64): clovo = "твой"; break;
	case(65): clovo = "хороший"; break;
	case(66): clovo = "некоторые (какой-то)"; break;
	case(67): clovo = "мог (прошедшее время. гл can)"; break;
	case(68): clovo = "им "; break;
	case(69): clovo = "видеть"; break;
	case(70): clovo = "другой"; break;
	case(71): clovo = "чем"; break;
	case(72): clovo = "затем"; break;
	case(73): clovo = "сейчас"; break;
	case(74): clovo = "смотреть"; break;
	case(75): clovo = "только"; break;
	case(76): clovo = "приходить"; break;
	case(77): clovo = "его"; break;
	case(78): clovo = "над"; break;
	case(79): clovo = "думать"; break;
	case(80): clovo = "также"; break;
	case(81): clovo = "назад"; break;
	case(82): clovo = "после"; break;
	case(83): clovo = "использовать"; break;
	case(84): clovo = "два"; break;
	case(85): clovo = "как"; break;
	case(86): clovo = "наш"; break;
	case(87): clovo = "работа"; break;
	case(88): clovo = "первый"; break;
	case(89): clovo = "хорошо"; break;
	case(90): clovo = "путь (способ)"; break;
	case(91): clovo = "даже"; break;
	case(92): clovo = "новый"; break;
	case(93): clovo = "хотеть"; break;
	case(94): clovo = "потому (потому, потому что)"; break;
	case(95): clovo = "любой"; break;
	case(96): clovo = "эти"; break;
	case(97): clovo = "давать"; break;
	case(98): clovo = "день"; break;
	case(99): clovo = "большинство"; break;
	case(100): clovo = "нас"; break;
	}
	return clovo;
}
string bloc_prost_eng(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "the"; break;
	case(2): clovo = "be"; break;
	case(3): clovo = "to"; break;
	case(4): clovo = "of"; break;
	case(5): clovo = "and"; break;
	case(6): clovo = "a"; break;
	case(7): clovo = "in"; break;
	case(8): clovo = "that"; break;
	case(9): clovo = "have"; break;
	case(10): clovo = "I"; break;
	case(11): clovo = "it"; break;
	case(12): clovo = "for"; break;
	case(13): clovo = "not"; break;
	case(14): clovo = "on"; break;
	case(15): clovo = "with"; break;
	case(16): clovo = "he"; break;
	case(17): clovo = "as"; break;
	case(18): clovo = "you"; break;
	case(19): clovo = "do"; break;
	case(20): clovo = "at"; break;
	case(21): clovo = "this"; break;
	case(22): clovo = "but"; break;
	case(23): clovo = "his"; break;
	case(24): clovo = "by"; break;
	case(25): clovo = "from"; break;
	case(26): clovo = "they"; break;
	case(27): clovo = "we"; break;
	case(28): clovo = "say"; break;
	case(29): clovo = "her"; break;
	case(30): clovo = "she"; break;
	case(31): clovo = "or"; break;
	case(32): clovo = "an"; break;
	case(33): clovo = "will"; break;
	case(34): clovo = "my"; break;
	case(35): clovo = "one"; break;
	case(36): clovo = "all"; break;
	case(37): clovo = "would"; break;
	case(38): clovo = "there"; break;
	case(39): clovo = "their"; break;
	case(40): clovo = "what"; break;
	case(41): clovo = "so"; break;
	case(42): clovo = "up"; break;
	case(43): clovo = "out"; break;
	case(44): clovo = "if"; break;
	case(45): clovo = "about"; break;
	case(46): clovo = "who"; break;
	case(47): clovo = "get"; break;
	case(48): clovo = "which"; break;
	case(49): clovo = "go"; break;
	case(50): clovo = "me"; break;
	case(51): clovo = "when"; break;
	case(52): clovo = "make"; break;
	case(53): clovo = "can"; break;
	case(54): clovo = "like"; break;
	case(55): clovo = "time"; break;
	case(56): clovo = "no"; break;
	case(57): clovo = "just"; break;
	case(58): clovo = "him"; break;
	case(59): clovo = "know"; break;
	case(60): clovo = "take"; break;
	case(61): clovo = "people"; break;
	case(62): clovo = "into"; break;
	case(63): clovo = "year"; break;
	case(64): clovo = "your"; break;
	case(65): clovo = "good"; break;
	case(66): clovo = "some"; break;
	case(67): clovo = "could"; break;
	case(68): clovo = "them"; break;
	case(69): clovo = "see"; break;
	case(70): clovo = "other"; break;
	case(71): clovo = "than"; break;
	case(72): clovo = "then"; break;
	case(73): clovo = "now"; break;
	case(74): clovo = "look"; break;
	case(75): clovo = "only"; break;
	case(76): clovo = "come"; break;
	case(77): clovo = "its"; break;
	case(78): clovo = "over"; break;
	case(79): clovo = "think"; break;
	case(80): clovo = "also"; break;
	case(81): clovo = "back"; break;
	case(82): clovo = "after"; break;
	case(83): clovo = "use"; break;
	case(84): clovo = "two"; break;
	case(85): clovo = "how"; break;
	case(86): clovo = "our"; break;
	case(87): clovo = "work"; break;
	case(88): clovo = "first"; break;
	case(89): clovo = "well"; break;
	case(90): clovo = "way"; break;
	case(91): clovo = "even"; break;
	case(92): clovo = "new"; break;
	case(93): clovo = "want"; break;
	case(94): clovo = "because"; break;
	case(95): clovo = "any"; break;
	case(96): clovo = "these"; break;
	case(97): clovo = "give"; break;
	case(98): clovo = "day"; break;
	case(99): clovo = "most"; break;
	case(100): clovo = "us"; break;
	}
	return clovo;
}
string bloc_sush_rus(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "время"; break;
	case(2): clovo = "год"; break;
	case(3): clovo = "люди"; break;
	case(4): clovo = "путь"; break;
	case(5): clovo = "день"; break;
	case(6): clovo = "мужчина"; break;
	case(7): clovo = "вещь"; break;
	case(8): clovo = "женщина"; break;
	case(9): clovo = "жизнь"; break;
	case(10): clovo = "ребенок"; break;
	case(11): clovo = "мир"; break;
	case(12): clovo = "школа"; break;
	case(13): clovo = "штат (состояние, штат)"; break;
	case(14): clovo = "семья"; break;
	case(15): clovo = "студент (ученик)"; break;
	case(16): clovo = "группа"; break;
	case(17): clovo = "страна"; break;
	case(18): clovo = "проблема"; break;
	case(19): clovo = "рука"; break;
	case(20): clovo = "часть"; break;
	case(21): clovo = "место"; break;
	case(22): clovo = "случай (ситуация,дело)"; break;
	case(23): clovo = "неделя"; break;
	case(24): clovo = "компания"; break;
	case(25): clovo = "система"; break;
	case(26): clovo = "программа"; break;
	case(27): clovo = "вопрос"; break;
	case(28): clovo = "работа"; break;
	case(29): clovo = "правительство"; break;
	case(30): clovo = "номер"; break;
	case(31): clovo = "ночь"; break;
	case(32): clovo = "точка"; break;
	case(33): clovo = "дом (домашний очаг)"; break;
	case(34): clovo = "вода"; break;
	case(35): clovo = "комната"; break;
	case(36): clovo = "мама"; break;
	case(37): clovo = "область (территория)"; break;
	case(38): clovo = "деньги"; break;
	case(39): clovo = "история (рассказ)"; break;
	case(40): clovo = "факт"; break;
	case(41): clovo = "месяц"; break;
	case(42): clovo = "партия (например книг), много"; break;
	case(43): clovo = "право"; break;
	case(44): clovo = "учеба (исследование)"; break;
	case(45): clovo = "книга"; break;
	case(46): clovo = "глаз"; break;
	case(47): clovo = "работа"; break;
	case(48): clovo = "слово"; break;
	case(49): clovo = "бизнес"; break;
	case(50): clovo = "дело (дело, случай, выпуск)"; break;
	case(51): clovo = "сторона"; break;
	case(52): clovo = "разновидность"; break;
	case(53): clovo = "голова"; break;
	case(54): clovo = "дом"; break;
	case(55): clovo = "услуга"; break;
	case(56): clovo = "друг"; break;
	case(57): clovo = "отец"; break;
	case(58): clovo = "сила (мощь, власть)"; break;
	case(59): clovo = "час"; break;
	case(60): clovo = "игра"; break;
	case(61): clovo = "линия"; break;
	case(62): clovo = "конец"; break;
	case(63): clovo = "член"; break;
	case(64): clovo = "закон"; break;
	case(65): clovo = "автомобиль"; break;
	case(66): clovo = "город"; break;
	case(67): clovo = "сообщество"; break;
	case(68): clovo = "имя"; break;
	case(69): clovo = "президент"; break;
	case(70): clovo = "команда"; break;
	case(71): clovo = "минута"; break;
	case(72): clovo = "идея"; break;
	case(73): clovo = "ребенок"; break;
	case(74): clovo = "тело"; break;
	case(75): clovo = "информация"; break;
	case(76): clovo = "спина"; break;
	case(77): clovo = "родитель"; break;
	case(78): clovo = "лицо"; break;
	case(79): clovo = "другие"; break;
	case(80): clovo = "уровень"; break;
	case(81): clovo = "офис"; break;
	case(82): clovo = "дверь"; break;
	case(83): clovo = "здоровье"; break;
	case(84): clovo = "человек"; break;
	case(85): clovo = "искусство"; break;
	case(86): clovo = "война"; break;
	case(87): clovo = "история"; break;
	case(88): clovo = "вечеринка"; break;
	case(89): clovo = "результат"; break;
	case(90): clovo = "замена"; break;
	case(91): clovo = "утро"; break;
	case(92): clovo = "причина"; break;
	case(93): clovo = "исследование"; break;
	case(94): clovo = "девушка"; break;
	case(95): clovo = "парень"; break;
	case(96): clovo = "момент"; break;
	case(97): clovo = "воздух"; break;
	case(98): clovo = "учитель"; break;
	case(99): clovo = "сила"; break;
	case(100): clovo = "образование"; break;
	}
	return clovo;
}
string bloc_sush_eng(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "time"; break;
	case(2): clovo = "year"; break;
	case(3): clovo = "people"; break;
	case(4): clovo = "way"; break;
	case(5): clovo = "day"; break;
	case(6): clovo = "man"; break;
	case(7): clovo = "thing"; break;
	case(8): clovo = "woman"; break;
	case(9): clovo = "life"; break;
	case(10): clovo = "child"; break;
	case(11): clovo = "world"; break;
	case(12): clovo = "school"; break;
	case(13): clovo = "state"; break;
	case(14): clovo = "family"; break;
	case(15): clovo = "student"; break;
	case(16): clovo = "group"; break;
	case(17): clovo = "country"; break;
	case(18): clovo = "problem"; break;
	case(19): clovo = "hand"; break;
	case(20): clovo = "part"; break;
	case(21): clovo = "place"; break;
	case(22): clovo = "case"; break;
	case(23): clovo = "week"; break;
	case(24): clovo = "company"; break;
	case(25): clovo = "system"; break;
	case(26): clovo = "program"; break;
	case(27): clovo = "question"; break;
	case(28): clovo = "work"; break;
	case(29): clovo = "government"; break;
	case(30): clovo = "number"; break;
	case(31): clovo = "night"; break;
	case(32): clovo = "point"; break;
	case(33): clovo = "home"; break;
	case(34): clovo = "water"; break;
	case(35): clovo = "room"; break;
	case(36): clovo = "mother"; break;
	case(37): clovo = "area"; break;
	case(38): clovo = "money"; break;
	case(39): clovo = "story"; break;
	case(40): clovo = "fact"; break;
	case(41): clovo = "month"; break;
	case(42): clovo = "lot"; break;
	case(43): clovo = "right"; break;
	case(44): clovo = "study"; break;
	case(45): clovo = "book"; break;
	case(46): clovo = "eye"; break;
	case(47): clovo = "job"; break;
	case(48): clovo = "word"; break;
	case(49): clovo = "business"; break;
	case(50): clovo = "issue"; break;
	case(51): clovo = "side"; break;
	case(52): clovo = "kind"; break;
	case(53): clovo = "head"; break;
	case(54): clovo = "house"; break;
	case(55): clovo = "service"; break;
	case(56): clovo = "friend"; break;
	case(57): clovo = "father"; break;
	case(58): clovo = "power"; break;
	case(59): clovo = "hour"; break;
	case(60): clovo = "game"; break;
	case(61): clovo = "line"; break;
	case(62): clovo = "end"; break;
	case(63): clovo = "member"; break;
	case(64): clovo = "law"; break;
	case(65): clovo = "car"; break;
	case(66): clovo = "city"; break;
	case(67): clovo = "community"; break;
	case(68): clovo = "name"; break;
	case(69): clovo = "president"; break;
	case(70): clovo = "team"; break;
	case(71): clovo = "minute"; break;
	case(72): clovo = "idea"; break;
	case(73): clovo = "kid"; break;
	case(74): clovo = "body"; break;
	case(75): clovo = "information"; break;
	case(76): clovo = "back"; break;
	case(77): clovo = "parent"; break;
	case(78): clovo = "face"; break;
	case(79): clovo = "others"; break;
	case(80): clovo = "level"; break;
	case(81): clovo = "office"; break;
	case(82): clovo = "door"; break;
	case(83): clovo = "health"; break;
	case(84): clovo = "person"; break;
	case(85): clovo = "art"; break;
	case(86): clovo = "war"; break;
	case(87): clovo = "history"; break;
	case(88): clovo = "party"; break;
	case(89): clovo = "result"; break;
	case(90): clovo = "change"; break;
	case(91): clovo = "morning"; break;
	case(92): clovo = "reason"; break;
	case(93): clovo = "research"; break;
	case(94): clovo = "girl"; break;
	case(95): clovo = "guy"; break;
	case(96): clovo = "moment"; break;
	case(97): clovo = "air"; break;
	case(98): clovo = "teacher"; break;
	case(99): clovo = "force"; break;
	case(100): clovo = "education"; break;
	}
	return clovo;
}

string bloc_glagol_rus(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "быть"; break;
	case(2): clovo = "иметь"; break;
	case(3): clovo = "делать"; break;
	case(4): clovo = "говорить"; break;
	case(5): clovo = "идти"; break;
	case(6): clovo = "мочь"; break;
	case(7): clovo = "получать"; break;
	case(8): clovo = "модуль (модальный глагол, выражающий\n желание, вероятность, просьбу)"; break;
	case(9): clovo = "делать"; break;
	case(10): clovo = "знать"; break;
	case(11): clovo = "хотеть"; break;
	case(12): clovo = "думать"; break;
	case(13): clovo = "брать"; break;
	case(14): clovo = "видеть"; break;
	case(15): clovo = "приходить"; break;
	case(16): clovo = "мог (глагол can в прош. времени)"; break;
	case(17): clovo = "хотеть"; break;
	case(18): clovo = "смотреть"; break;
	case(19): clovo = "использовать"; break;
	case(20): clovo = "находить"; break;
	case(21): clovo = "давать"; break;
	case(22): clovo = "говорить"; break;
	case(23): clovo = "работать"; break;
	case(24): clovo = "Модуль (модальный глагол, выражающий\n вероятность, разрешение)"; break;
	case(25): clovo = "Модуль (модальный глагол, выражающий\n долженствование)"; break;
	case(26): clovo = "вызывать"; break;
	case(27): clovo = "пробовать"; break;
	case(28): clovo = "спрашивать"; break;
	case(29): clovo = "нуждаться"; break;
	case(30): clovo = "чувствовать"; break;
	case(31): clovo = "становится"; break;
	case(32): clovo = "покидать"; break;
	case(33): clovo = "класть"; break;
	case(34): clovo = "значить"; break;
	case(35): clovo = "хранить (удерживать)"; break;
	case(36): clovo = "позволять"; break;
	case(37): clovo = "начинать"; break;
	case(38): clovo = "казаться"; break;
	case(39): clovo = "помогать"; break;
	case(40): clovo = "разговаривать"; break;
	case(41): clovo = "поворачивать"; break;
	case(42): clovo = "начинать"; break;
	case(43): clovo = "возможно (может быть, прош. форма\n глагола ман)"; break;
	case(44): clovo = "показывать"; break;
	case(45): clovo = "слышать"; break;
	case(46): clovo = "играть"; break;
	case(47): clovo = "бежать"; break;
	case(48): clovo = "двигать"; break;
	case(49): clovo = "нравиться"; break;
	case(50): clovo = "жить"; break;
	case(51): clovo = "верить (считать)"; break;
	case(52): clovo = "держать"; break;
	case(53): clovo = "носить"; break;
	case(54): clovo = "случаться"; break;
	case(55): clovo = "Модуль (модальный глагол, выражающий\n сильную степень долженствования)"; break;
	case(56): clovo = "писать"; break;
	case(57): clovo = "обеспечивать (предоставлять)"; break;
	case(58): clovo = "сидеть"; break;
	case(59): clovo = "стоять"; break;
	case(60): clovo = "терять"; break;
	case(61): clovo = "платить"; break;
	case(62): clovo = "встретить"; break;
	case(63): clovo = "включают"; break;
	case(64): clovo = "продолжить"; break;
	case(65): clovo = "устанавливать"; break;
	case(66): clovo = "изучать"; break;
	case(67): clovo = "изменять"; break;
	case(68): clovo = "водить"; break;
	case(69): clovo = "понимать"; break;
	case(70): clovo = "смотреть"; break;
	case(71): clovo = "следовать"; break;
	case(72): clovo = "останавливается"; break;
	case(73): clovo = "создавать"; break;
	case(74): clovo = "говорить"; break;
	case(75): clovo = "читать"; break;
	case(76): clovo = "позволять"; break;
	case(77): clovo = "добавлять"; break;
	case(78): clovo = "проводить (проводить (время), тратить)"; break;
	case(79): clovo = "расти"; break;
	case(80): clovo = "открывать"; break;
	case(81): clovo = "идти (шагать, идти пешком)"; break;
	case(82): clovo = "выигрывать"; break;
	case(83): clovo = "предлагать"; break;
	case(84): clovo = "помнить"; break;
	case(85): clovo = "любить"; break;
	case(86): clovo = "считать"; break;
	case(87): clovo = "появляться"; break;
	case(88): clovo = "покупать"; break;
	case(89): clovo = "ждать"; break;
	case(90): clovo = "обслуживать"; break;
	case(91): clovo = "умирать"; break;
	case(92): clovo = "отсылать"; break;
	case(93): clovo = "ожидать"; break;
	case(94): clovo = "строить"; break;
	case(95): clovo = "оставаться"; break;
	case(96): clovo = "падать"; break;
	case(97): clovo = "резать"; break;
	case(98): clovo = "достигать"; break;
	case(99): clovo = "убивать"; break;
	case(100): clovo = "сохранять"; break;
	}
	return clovo;
}

string bloc_glagol_eng(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "be"; break;
	case(2): clovo = "have"; break;
	case(3): clovo = "do"; break;
	case(4): clovo = "say"; break;
	case(5): clovo = "go"; break;
	case(6): clovo = "can"; break;
	case(7): clovo = "get"; break;
	case(8): clovo = "would"; break;
	case(9): clovo = "make"; break;
	case(10): clovo = "know"; break;
	case(11): clovo = "will"; break;
	case(12): clovo = "think"; break;
	case(13): clovo = "take"; break;
	case(14): clovo = "see"; break;
	case(15): clovo = "come"; break;
	case(16): clovo = "could"; break;
	case(17): clovo = "want"; break;
	case(18): clovo = "look"; break;
	case(19): clovo = "use"; break;
	case(20): clovo = "find"; break;
	case(21): clovo = "give"; break;
	case(22): clovo = "tell"; break;
	case(23): clovo = "work"; break;
	case(24): clovo = "may"; break;
	case(25): clovo = "should"; break;
	case(26): clovo = "call"; break;
	case(27): clovo = "try"; break;
	case(28): clovo = "ask"; break;
	case(29): clovo = "need"; break;
	case(30): clovo = "feel"; break;
	case(31): clovo = "become"; break;
	case(32): clovo = "leave"; break;
	case(33): clovo = "put"; break;
	case(34): clovo = "mean"; break;
	case(35): clovo = "keep"; break;
	case(36): clovo = "let"; break;
	case(37): clovo = "begin"; break;
	case(38): clovo = "seem"; break;
	case(39): clovo = "help"; break;
	case(40): clovo = "talk"; break;
	case(41): clovo = "turn"; break;
	case(42): clovo = "start"; break;
	case(43): clovo = "might"; break;
	case(44): clovo = "show"; break;
	case(45): clovo = "hear"; break;
	case(46): clovo = "play"; break;
	case(47): clovo = "run"; break;
	case(48): clovo = "move"; break;
	case(49): clovo = "like"; break;
	case(50): clovo = "live"; break;
	case(51): clovo = "believe"; break;
	case(52): clovo = "hold"; break;
	case(53): clovo = "bring"; break;
	case(54): clovo = "happen"; break;
	case(55): clovo = "must"; break;
	case(56): clovo = "write"; break;
	case(57): clovo = "provide"; break;
	case(58): clovo = "sit"; break;
	case(59): clovo = "stand"; break;
	case(60): clovo = "lose"; break;
	case(61): clovo = "pay"; break;
	case(62): clovo = "meet"; break;
	case(63): clovo = "include"; break;
	case(64): clovo = "continue"; break;
	case(65): clovo = "set"; break;
	case(66): clovo = "learn"; break;
	case(67): clovo = "change"; break;
	case(68): clovo = "lead"; break;
	case(69): clovo = "understand"; break;
	case(70): clovo = "watch"; break;
	case(71): clovo = "follow"; break;
	case(72): clovo = "stop"; break;
	case(73): clovo = "create"; break;
	case(74): clovo = "speak"; break;
	case(75): clovo = "read"; break;
	case(76): clovo = "allow"; break;
	case(77): clovo = "add"; break;
	case(78): clovo = "spend"; break;
	case(79): clovo = "grow"; break;
	case(80): clovo = "open"; break;
	case(81): clovo = "walk"; break;
	case(82): clovo = "win"; break;
	case(83): clovo = "offer"; break;
	case(84): clovo = "remember"; break;
	case(85): clovo = "love"; break;
	case(86): clovo = "consider"; break;
	case(87): clovo = "appear"; break;
	case(88): clovo = "buy"; break;
	case(89): clovo = "wait"; break;
	case(90): clovo = "serve"; break;
	case(91): clovo = "die"; break;
	case(92): clovo = "send"; break;
	case(93): clovo = "expect"; break;
	case(94): clovo = "build"; break;
	case(95): clovo = "stay"; break;
	case(96): clovo = "fall"; break;
	case(97): clovo = "cut"; break;
	case(98): clovo = "reach"; break;
	case(99): clovo = "kill"; break;
	case(100): clovo = "remain"; break;

	}
	return clovo;
}

string bloc_pril_rus(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "иной"; break;
	case(2): clovo = "новый"; break;
	case(3): clovo = "хороший"; break;
	case(4): clovo = "высокий"; break;
	case(5): clovo = "старый"; break;
	case(6): clovo = "великий"; break;
	case(7): clovo = "большой"; break;
	case(8): clovo = "американский"; break;
	case(9): clovo = "маленький"; break;
	case(10): clovo = "большой"; break;
	case(11): clovo = "национальный"; break;
	case(12): clovo = "молодой"; break;
	case(13): clovo = "различный"; break;
	case(14): clovo = "черный"; break;
	case(15): clovo = "длинный"; break;
	case(16): clovo = "маленький"; break;
	case(17): clovo = "важный"; break;
	case(18): clovo = "политический"; break;
	case(19): clovo = "плохой"; break;
	case(20): clovo = "белый"; break;
	case(21): clovo = "настоящий"; break;
	case(22): clovo = "лучший"; break;
	case(23): clovo = "правильный"; break;
	case(24): clovo = "общественный"; break;
	case(25): clovo = "единственный"; break;
	case(26): clovo = "публичный"; break;
	case(27): clovo = "уверенный"; break;
	case(28): clovo = "низкий"; break;
	case(29): clovo = "ранний"; break;
	case(30): clovo = "компетентный"; break;
	case(31): clovo = "человечный"; break;
	case(32): clovo = "местный"; break;
	case(33): clovo = "поздний"; break;
	case(34): clovo = "жесткий"; break;
	case(35): clovo = "основной"; break;
	case(36): clovo = "лучший"; break;
	case(37): clovo = "экономический"; break;
	case(38): clovo = "сильный"; break;
	case(39): clovo = "возможный"; break;
	case(40): clovo = "цельный"; break;
	case(41): clovo = "свободный"; break;
	case(42): clovo = "военный"; break;
	case(43): clovo = "верный"; break;
	case(44): clovo = "федеральный"; break;
	case(45): clovo = "международный"; break;
	case(46): clovo = "полный"; break;
	case(47): clovo = "особый"; break;
	case(48): clovo = "легкий"; break;
	case(49): clovo = "понятный"; break;
	case(50): clovo = "недавний"; break;
	case(51): clovo = "определенный"; break;
	case(52): clovo = "личный"; break;
	case(53): clovo = "открытый"; break;
	case(54): clovo = "красный"; break;
	case(55): clovo = "трудный"; break;
	case(56): clovo = "доступный"; break;
	case(57): clovo = "вероятный"; break;
	case(58): clovo = "короткий"; break;
	case(59): clovo = "одинокий"; break;
	case(60): clovo = "медицинский"; break;
	case(61): clovo = "текущий"; break;
	case(62): clovo = "неправильный"; break;
	case(63): clovo = "личный"; break;
	case(64): clovo = "прошлый"; break;
	case(65): clovo = "иностранный"; break;
	case(66): clovo = "хороший"; break;
	case(67): clovo = "общий"; break;
	case(68): clovo = "бедный"; break;
	case(69): clovo = "естественный"; break;
	case(70): clovo = "существенный"; break;
	case(71): clovo = "похожий"; break;
	case(72): clovo = "горячий"; break;
	case(73): clovo = "мертвый"; break;
	case(74): clovo = "центральный"; break;
	case(75): clovo = "счастливый"; break;
	case(76): clovo = "серьезный"; break;
	case(77): clovo = "готовый"; break;
	case(78): clovo = "простой"; break;
	case(79): clovo = "левый"; break;
	case(80): clovo = "физический"; break;
	case(81): clovo = "общий"; break;
	case(82): clovo = "экологический"; break;
	case(83): clovo = "финансовый"; break;
	case(84): clovo = "синий"; break;
	case(85): clovo = "демократический"; break;
	case(86): clovo = "темный"; break;
	case(87): clovo = "различный"; break;
	case(88): clovo = "целый"; break;
	case(89): clovo = "близкий"; break;
	case(90): clovo = "законный"; break;
	case(91): clovo = "религиозный"; break;
	case(92): clovo = "холодный"; break;
	case(93): clovo = "конечный"; break;
	case(94): clovo = "главный"; break;
	case(95): clovo = "зеленый"; break;
	case(96): clovo = "милый"; break;
	case(97): clovo = "огромный"; break;
	case(98): clovo = "известный"; break;
	case(99): clovo = "традиционный"; break;
	case(100): clovo = "культурный"; break;
	}
	return clovo;
}
string bloc_pril_eng(int x) {
	string clovo;
	switch (x) {
	case(1): clovo = "other"; break;
	case(2): clovo = "new"; break;
	case(3): clovo = "good"; break;
	case(4): clovo = "high"; break;
	case(5): clovo = "old"; break;
	case(6): clovo = "great"; break;
	case(7): clovo = "big"; break;
	case(8): clovo = "american"; break;
	case(9): clovo = "small"; break;
	case(10): clovo = "large"; break;
	case(11): clovo = "national"; break;
	case(12): clovo = "young"; break;
	case(13): clovo = "different"; break;
	case(14): clovo = "black"; break;
	case(15): clovo = "long"; break;
	case(16): clovo = "little"; break;
	case(17): clovo = "important"; break;
	case(18): clovo = "political"; break;
	case(19): clovo = "bad"; break;
	case(20): clovo = "white"; break;
	case(21): clovo = "real"; break;
	case(22): clovo = "best"; break;
	case(23): clovo = "right"; break;
	case(24): clovo = "social"; break;
	case(25): clovo = "only"; break;
	case(26): clovo = "public"; break;
	case(27): clovo = "sure"; break;
	case(28): clovo = "low"; break;
	case(29): clovo = "early"; break;
	case(30): clovo = "able"; break;
	case(31): clovo = "human"; break;
	case(32): clovo = "local"; break;
	case(33): clovo = "late"; break;
	case(34): clovo = "hard"; break;
	case(35): clovo = "major"; break;
	case(36): clovo = "better"; break;
	case(37): clovo = "economic"; break;
	case(38): clovo = "strong"; break;
	case(39): clovo = "possible"; break;
	case(40): clovo = "whole"; break;
	case(41): clovo = "free"; break;
	case(42): clovo = "military"; break;
	case(43): clovo = "true"; break;
	case(44): clovo = "federal"; break;
	case(45): clovo = "international"; break;
	case(46): clovo = "full"; break;
	case(47): clovo = "special"; break;
	case(48): clovo = "easy"; break;
	case(49): clovo = "clear"; break;
	case(50): clovo = "recent"; break;
	case(51): clovo = "certain"; break;
	case(52): clovo = "personal"; break;
	case(53): clovo = "open"; break;
	case(54): clovo = "red"; break;
	case(55): clovo = "difficult"; break;
	case(56): clovo = "available"; break;
	case(57): clovo = "likely"; break;
	case(58): clovo = "short"; break;
	case(59): clovo = "single"; break;
	case(60): clovo = "medical"; break;
	case(61): clovo = "current"; break;
	case(62): clovo = "wrong"; break;
	case(63): clovo = "private"; break;
	case(64): clovo = "past"; break;
	case(65): clovo = "foreign"; break;
	case(66): clovo = "fine"; break;
	case(67): clovo = "common"; break;
	case(68): clovo = "poor"; break;
	case(69): clovo = "natural"; break;
	case(70): clovo = "significant"; break;
	case(71): clovo = "similar"; break;
	case(72): clovo = "hot"; break;
	case(73): clovo = "dead"; break;
	case(74): clovo = "central"; break;
	case(75): clovo = "happy"; break;
	case(76): clovo = "serious"; break;
	case(77): clovo = "ready"; break;
	case(78): clovo = "simple"; break;
	case(79): clovo = "left"; break;
	case(80): clovo = "physical"; break;
	case(81): clovo = "general"; break;
	case(82): clovo = "environmental"; break;
	case(83): clovo = "financial"; break;
	case(84): clovo = "blue"; break;
	case(85): clovo = "democratic"; break;
	case(86): clovo = "dark"; break;
	case(87): clovo = "various"; break;
	case(88): clovo = "entire"; break;
	case(89): clovo = "close"; break;
	case(90): clovo = "legal"; break;
	case(91): clovo = "religious"; break;
	case(92): clovo = "cold"; break;
	case(93): clovo = "final"; break;
	case(94): clovo = "main"; break;
	case(95): clovo = "green"; break;
	case(96): clovo = "nice"; break;
	case(97): clovo = "huge"; break;
	case(98): clovo = "popular"; break;
	case(99): clovo = "traditional"; break;
	case(100): clovo = "cultural"; break;
	}
	return clovo;
}

