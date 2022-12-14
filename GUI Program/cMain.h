#pragma once
#include "wx/wx.h"
#include <wx/statline.h>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

//game logic class
class GameLogic
{
private:
	string CurrentPlayer;
	string Bplayer_Label, Rplayer_Label;
	string CurrentGameMode;
	string Bplayer_Human_or_AI, Rplayer_Human_or_AI;

public:
	int Bplayer_SOS_counter = 0, Rplayer_SOS_counter = 0;
	int total_buttons, already_fill_out = 0;
	string simple_Game = "SimpleGame", general_Game = "GeneralGame";
	string Bplayer = "Blue", Rplayer = "Red";
	const string s = "S";
	const string o = "O";
	bool GameDone = false;
	vector<vector<string>> Two_D_matrix;
	vector< pair <int, int>> Vector_of_Adjacent_elements;

	void Set_Bplayer_Human_or_AI(string label)
	{
		Bplayer_Human_or_AI = label;
	}

	void Set_Rplayer_Human_or_AI(string label)
	{
		Rplayer_Human_or_AI = label;
	}

	string Get_Bplayer_Human_or_AI()
	{
		return Bplayer_Human_or_AI;
	}

	string Get_Rplayer_Human_or_AI()
	{
		return Rplayer_Human_or_AI;
	}

	void Set_Bplayer_Label(string label)
	{
		Bplayer_Label = label;
	}

	string Get_Bplayer_Label()
	{
		return Bplayer_Label;
	}

	void Set_Rplayer_Label(string label)
	{
		Rplayer_Label = label;
	}

	string Get_Rplayer_Label()
	{
		return Rplayer_Label;
	}

	void SetCurrentPlayer(string input)
	{
		CurrentPlayer = input;
	}

	string GetCurrentPlayer()
	{
		return CurrentPlayer;
	}

	//Checks current player and then swaps to the next player to change turns
	void SetNextPlayer()
	{
		if (CurrentPlayer == Rplayer)
		{
			CurrentPlayer = Bplayer;
		}
		else
		{
			CurrentPlayer = Rplayer;
		}
	}

	void SetNextPlayer_AI_involved()
	{
		if (CurrentPlayer == "Human")
		{
			CurrentPlayer = "Computer";
		}
		else
		{
			CurrentPlayer = "Human";
		}
	}

	void SetGameMode(string modeInput)
	{
		if (modeInput == simple_Game)
		{
			CurrentGameMode = simple_Game;
		}
		if (modeInput == general_Game)
		{
			CurrentGameMode = general_Game;
		}
	}

	string GetGameMode()
	{
		return CurrentGameMode;
	}

	bool PlayerWin()
	{
		return true;
	}

	bool isValidPos(int i, int j, int n, int m)
	{
		if (i < 0 || j < 0 || i > n - 1 || j > m - 1)
			return 0;
		return 1;
	}

	vector< pair <int, int>> getAdjacent(vector<vector<string> >& arr, int i, int j)
	{
		int n = arr.size();
		int m = arr[0].size();

		vector< pair <int, int>> v;
		pair<int, int> index;

		if (isValidPos(i - 1, j - 1, n, m))
		{
			index.first = i - 1;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i - 1, j, n, m))
		{
			index.first = i - 1;
			index.second = j;
			v.push_back(index);
		}
		if (isValidPos(i - 1, j + 1, n, m))
		{
			index.first = i - 1;
			index.second = j + 1;
			v.push_back(index);
		}
		if (isValidPos(i, j - 1, n, m))
		{
			index.first = i;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i, j + 1, n, m))
		{
			index.first = i;
			index.second = j + 1;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j - 1, n, m))
		{
			index.first = i + 1;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j, n, m))
		{
			index.first = i + 1;
			index.second = j;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j + 1, n, m))
		{
			index.first = i + 1;
			index.second = j + 1;
			v.push_back(index);
		}

		return v;
	}

	bool O_scenerio_checker(vector<vector<string>> second_Two_D_matrix, int n, int m, int i, int j)						//in parameter (2d vector, height, width, index 1, index 2)
	{
		if (isValidPos(i - 1, j, n, m) == 1 && isValidPos(i + 1, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i - 1][j] == "S" && second_Two_D_matrix[i + 1][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j - 1, n, m) == 1 && isValidPos(i, j + 1, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i][j - 1] == "S" && second_Two_D_matrix[i][j + 1] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j - 1, n, m) == 1 && isValidPos(i + 1, j + 1, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i - 1][j - 1] == "S" && second_Two_D_matrix[i + 1][j + 1] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j - 1, n, m) == 1 && isValidPos(i - 1, j + 1, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i + 1][j - 1] == "S" && second_Two_D_matrix[i - 1][j + 1] == "S")
			{
				return true;
			}
		}
	}

	bool S_scenerio_checker(vector<vector<string>> second_Two_D_matrix, int n, int m , int i, int j)    //in parameter (2d vector, height, width, index 1, index 2)
	{
		if (isValidPos(i + 1, j + 1, n, m) == 1 && isValidPos(i + 2, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j + 1] == "O" && second_Two_D_matrix[i + 2][j + 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j, n, m) == 1 && isValidPos(i + 2, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j] == "O" && second_Two_D_matrix[i + 2][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j - 1, n, m) == 1 && isValidPos(i + 2, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j - 1] == "O" && second_Two_D_matrix[i + 2][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j - 1, n, m) == 1 && isValidPos(i, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i][j - 1] == "O" && second_Two_D_matrix[i][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j - 1, n, m) == 1 && isValidPos(i - 2, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j - 1] == "O" && second_Two_D_matrix[i - 2][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j, n, m) == 1 && isValidPos(i - 2, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j] == "O" && second_Two_D_matrix[i - 2][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j + 1, n, m) == 1 && isValidPos(i - 2, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j + 1] == "O" && second_Two_D_matrix[i - 2][j + 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j + 1, n, m) == 1 && isValidPos(i, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i][j + 1] == "O" && second_Two_D_matrix[i][j + 2] == "S")
			{
				return true;
			}
		}
	}
};

class Computer : public GameLogic
{
private:
	string AI_Label;
	
public:

	int AI_length = 0;

	void Set_AI_label()   //randomize set label between S or O 
	{
		srand(time(0));  // Initialize random number generator.
		int n = rand() % 6;
		if (n % 2 == 0)
		{
			AI_Label = "S";
		}
		else
		{
			AI_Label = "O";
		}
	}

	pair<int, int> AI_placement_on_2d_matrix(vector<vector<string>> Two_D_Matrix)
	{
		int x, y, z;
		pair<int, int> temp_pair;
		vector<pair<int, int>> unoccupied_space;

		for (int i = 0; i < Two_D_Matrix.size(); i++)
		{
			for (int j = 0; j < Two_D_Matrix.size(); j++)
			{
				if (Two_D_Matrix[i][j] == " ")
				{
					temp_pair.first = i;
					temp_pair.second = j;
					unoccupied_space.push_back(temp_pair);
				}
			}
		}

		if (unoccupied_space.size() != 0)
		{
			z = rand() % unoccupied_space.size();
			return unoccupied_space.at(z);
		}
		else
		{
			return make_pair(-1,-1);
		}
	}

	string Get_AI_Label()
	{
		return AI_Label;
	}
};


class UI : public wxFrame
{
	//put cMain class into this
	//create this class GameLogic_object in CMain as for GameLogic
	//might fix the restart, new game option
private:
	int length = 0;

	//add components into window 
public:
	int length_int = 0;
	string length_string;
	wxStaticText* m_txt2 = nullptr, * m_txt3 = nullptr;
	wxStaticLine* m_staticline1;
	wxTextCtrl* m_txt1 = nullptr;
	wxCheckBox* m_cbox1 = nullptr;
	wxRadioButton* m_radiobtn1, * m_radiobtn2, * m_radiobtn3, * m_radiobtn4, * m_radiobtn5,* m_radiobtn7, * m_radiobtn8, * m_radiobtn9, * m_radiobtn10, * m_radiobtn6 = nullptr;
	wxListBox* m_list1 = nullptr;
	//wxButton* m_btn1 = nullptr;
	wxButton* new_Game, *AI_move, *Replay = nullptr;
	
	bool is_that_an_SOS = false;

	wxButton** btn = new wxButton * [length_int * length_int];

	wxGridSizer* buttonSizer = new wxGridSizer(length_int, length_int, 0, 0);								        // ( row, column, horz gap, vert gap )

	//object of classes
	GameLogic* GameLogic_object = new GameLogic;
	Computer* AI_object = new Computer;


	//function
	void set_Length(int x)
	{
		length = x;
	}

	int get_Length()
	{
		return length;
	}

	//disable all button on table to prevent further input
	void Blank_out_Table(int lengthx)
	{
		for (int x = 0; x < lengthx; x++)
		{
			for (int y = 0; y < lengthx; y++)
			{
				btn[y * lengthx + x]->Enable(false);
			}
		}
	}

};


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:
	UI* UI_object = new UI;
	string previous_game_winner; // set this on a different class since this will be reset once "Restart" button hit
	bool is_Recording = false;
	//initialize SOS panel of button with pre-fix value - length_int - for panel size  
	wxPanel* bgPanel = new wxPanel(this, wxID_ANY, wxPoint(170, 70), wxSize(200, 200));

	//declare event
	void BoardSize(wxCommandEvent& evt);
	void OnButtonClicked(wxCommandEvent& evt);
	void Simple_game_Checked(wxCommandEvent& evt);
	void General_game_Checked(wxCommandEvent& evt);
	void Bplayer_S_Checked(wxCommandEvent& evt);
	void Bplayer_O_Checked(wxCommandEvent& evt);
	void Rplayer_S_Checked(wxCommandEvent& evt);
	void Rplayer_O_Checked(wxCommandEvent& evt);
	void Restart(wxCommandEvent& evt);
	void AI_OnButtonClicked(wxCommandEvent& evt);
	void Bplayer_Human_Checked(wxCommandEvent& evt);
	void Bplayer_AI_Checked(wxCommandEvent& evt);
	void Rplayer_Human_Checked(wxCommandEvent& evt);
	void Rplayer_AI_Checked(wxCommandEvent& evt);
	void Record(wxCommandEvent& evt);
	void Replay(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();

	void InitializeTable(wxFont font, int lengthx)                                                                       //panel of button for SOS placement
	{
		//updating value for panel size n*n base on user input 
		UI_object->btn = new wxButton * [lengthx * lengthx];
		UI_object->buttonSizer = new wxGridSizer(lengthx, lengthx, 0, 0);								        // ( row, column, horz gap, vert gap )

		for (int x = 0; x < lengthx; x++)
		{
			for (int y = 0; y < lengthx; y++)
			{
				UI_object->btn[y * lengthx + x] = new wxButton(bgPanel, 10000 + (y * lengthx + x));                      //create new button and give it a unique id
				UI_object->btn[y * lengthx + x]->SetFont(font);                                                         //set font to that instance for better visual
				UI_object->buttonSizer->Add(UI_object->btn[y * lengthx + x], 1, wxEXPAND | wxALL);                                 //add button to wxGridSizer

				UI_object->btn[y * lengthx + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);     //bind event handler to button when clicked
			}

			bgPanel->SetSizer(UI_object->buttonSizer);
			bgPanel->Layout();
		}
	}

	void InitializeComponent()
	{
		UI_object->m_txt2 = new wxStaticText(this, wxID_ANY, "SOS", wxPoint(130, 21), wxSize(50, 50));
		UI_object->m_txt2 = new wxStaticText(this, wxID_ANY, "Current turn:", wxPoint(220, 275), wxSize(100, 50));
		UI_object->m_txt3 = new wxStaticText(this, wxID_ANY, UI_object->GameLogic_object->GetCurrentPlayer() + " Player", wxPoint(320, 275), wxSize(150, 50));
		UI_object->m_txt2 = new wxStaticText(this, wxID_ANY, "Blue Player", wxPoint(10, 80), wxSize(100, 35));
		UI_object->m_txt2 = new wxStaticText(this, wxID_ANY, "Red Player", wxPoint(470, 80), wxSize(100, 35));
		UI_object->m_txt2 = new wxStaticText(this, wxID_ANY, "Board size", wxPoint(450, 22), wxSize(70, 50));
		UI_object->m_txt1 = new wxTextCtrl(this, 1000, UI_object->length_string, wxPoint(510, 19), wxSize(25, 25), wxTE_PROCESS_ENTER);
		UI_object->m_radiobtn1 = new wxRadioButton(this, 1001, "Simple game", wxPoint(190, 5), wxSize(100, 50), wxRB_GROUP);
		UI_object->m_radiobtn2 = new wxRadioButton(this, 1002, "General game", wxPoint(330, 5), wxSize(100, 50));
		UI_object->m_radiobtn3 = new wxRadioButton(this, 1011, "S", wxPoint(30, 160), wxSize(35, 35), wxRB_GROUP);
		UI_object->m_radiobtn4 = new wxRadioButton(this, 1022, "O", wxPoint(30, 190), wxSize(35, 35));
		UI_object->m_radiobtn5 = new wxRadioButton(this, 1033, "S", wxPoint(490, 160), wxSize(35, 35), wxRB_GROUP);
		UI_object->m_radiobtn6 = new wxRadioButton(this, 1044, "O", wxPoint(490, 190), wxSize(35, 35));
		UI_object->m_radiobtn8 = new wxRadioButton(this, 1066, "Computer", wxPoint(10, 100), wxSize(70, 35), wxRB_GROUP);
		UI_object->m_radiobtn7 = new wxRadioButton(this, 1055, "Human", wxPoint(10, 130), wxSize(70, 35));
		UI_object->m_radiobtn10 = new wxRadioButton(this, 1088, "Computer", wxPoint(470, 100), wxSize(70, 35), wxRB_GROUP);
		UI_object->m_radiobtn9 = new wxRadioButton(this, 1077, "Human", wxPoint(470, 130), wxSize(70, 35));
		UI_object->new_Game = new wxButton(this, 2002, "New Game", wxPoint(470, 270), wxSize(70, 25));
		UI_object->m_cbox1 = new wxCheckBox(this, 4004, "Record Game", wxPoint(30, 270), wxSize(90, 25));
	}
};

class SimpleGame : GameLogic
{
	vector<vector<string>> Two_D_matrix;
	vector< pair <int, int>> Vector_of_Adjacent_elements;
	int total_buttons, already_fill_out = 0;

	bool isValidPos(int i, int j, int n, int m)
	{
		if (i < 0 || j < 0 || i > n - 1 || j > m - 1)
			return 0;
		return 1;
	}

	vector< pair <int, int>> getAdjacent(vector<vector<string> >& arr, int i, int j)
	{
		int n = arr.size();
		int m = arr[0].size();

		vector< pair <int, int>> v;
		pair<int, int> index;

		if (isValidPos(i - 1, j - 1, n, m))
		{
			index.first = i - 1;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i - 1, j, n, m))
		{
			index.first = i - 1;
			index.second = j;
			v.push_back(index);
		}
		if (isValidPos(i - 1, j + 1, n, m))
		{
			index.first = i - 1;
			index.second = j + 1;
			v.push_back(index);
		}
		if (isValidPos(i, j - 1, n, m))
		{
			index.first = i;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i, j + 1, n, m))
		{
			index.first = i;
			index.second = j + 1;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j - 1, n, m))
		{
			index.first = i + 1;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j, n, m))
		{
			index.first = i + 1;
			index.second = j;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j + 1, n, m))
		{
			index.first = i + 1;
			index.second = j + 1;
			v.push_back(index);
		}

		return v;
	}

	bool O_scenerio_checker(vector< pair <int, int>> Vector_of_Adjacent_elements)
	{
		switch (Vector_of_Adjacent_elements.size())
		{
		case 5:
			if (Two_D_matrix[Vector_of_Adjacent_elements[0].first][Vector_of_Adjacent_elements[0].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[3].first][Vector_of_Adjacent_elements[3].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[0].first][Vector_of_Adjacent_elements[0].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[1].first][Vector_of_Adjacent_elements[1].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[3].first][Vector_of_Adjacent_elements[3].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[4].first][Vector_of_Adjacent_elements[4].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[1].first][Vector_of_Adjacent_elements[1].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[4].first][Vector_of_Adjacent_elements[4].second] == "S")
			{
				return true;
			}
			break;

		case 8:
			if (Two_D_matrix[Vector_of_Adjacent_elements[0].first][Vector_of_Adjacent_elements[0].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[7].first][Vector_of_Adjacent_elements[7].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[2].first][Vector_of_Adjacent_elements[2].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[5].first][Vector_of_Adjacent_elements[5].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[1].first][Vector_of_Adjacent_elements[1].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[6].first][Vector_of_Adjacent_elements[6].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[3].first][Vector_of_Adjacent_elements[3].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[4].first][Vector_of_Adjacent_elements[4].second] == "S")
			{
				return true;
			}
			break;

		default:
			return false;
		}
	}

	bool S_scenerio_checker(vector<vector<string>> second_Two_D_matrix, int n, int m, int i, int j)    //in parameter (2d vector, height, width, index 1, index 2)
	{
		if (isValidPos(i + 1, j + 1, n, m) == 1 && isValidPos(i + 2, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j + 1] == "O" && second_Two_D_matrix[i + 2][j + 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j, n, m) == 1 && isValidPos(i + 2, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j] == "O" && second_Two_D_matrix[i + 2][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j - 1, n, m) == 1 && isValidPos(i + 2, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j - 1] == "O" && second_Two_D_matrix[i + 2][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j - 1, n, m) == 1 && isValidPos(i, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i][j - 1] == "O" && second_Two_D_matrix[i][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j - 1, n, m) == 1 && isValidPos(i - 2, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j - 1] == "O" && second_Two_D_matrix[i - 2][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j, n, m) == 1 && isValidPos(i - 2, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j] == "O" && second_Two_D_matrix[i - 2][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j + 1, n, m) == 1 && isValidPos(i - 2, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j + 1] == "O" && second_Two_D_matrix[i - 2][j + 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j + 1, n, m) == 1 && isValidPos(i, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i][j + 1] == "O" && second_Two_D_matrix[i][j + 2] == "S")
			{
				return true;
			}
		}
	}
};

class GeneralGame : GameLogic
{
	vector<vector<string>> Two_D_matrix;
	vector< pair <int, int>> Vector_of_Adjacent_elements;
	int total_buttons, already_fill_out = 0;

	bool isValidPos(int i, int j, int n, int m)
	{
		if (i < 0 || j < 0 || i > n - 1 || j > m - 1)
			return 0;
		return 1;
	}

	vector< pair <int, int>> getAdjacent(vector<vector<string> >& arr, int i, int j)
	{
		int n = arr.size();
		int m = arr[0].size();

		vector< pair <int, int>> v;
		pair<int, int> index;

		if (isValidPos(i - 1, j - 1, n, m))
		{
			index.first = i - 1;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i - 1, j, n, m))
		{
			index.first = i - 1;
			index.second = j;
			v.push_back(index);
		}
		if (isValidPos(i - 1, j + 1, n, m))
		{
			index.first = i - 1;
			index.second = j + 1;
			v.push_back(index);
		}
		if (isValidPos(i, j - 1, n, m))
		{
			index.first = i;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i, j + 1, n, m))
		{
			index.first = i;
			index.second = j + 1;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j - 1, n, m))
		{
			index.first = i + 1;
			index.second = j - 1;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j, n, m))
		{
			index.first = i + 1;
			index.second = j;
			v.push_back(index);
		}
		if (isValidPos(i + 1, j + 1, n, m))
		{
			index.first = i + 1;
			index.second = j + 1;
			v.push_back(index);
		}

		return v;
	}
	/*
	bool O_scenerio_checker(vector< pair <int, int>> Vector_of_Adjacent_elements)
	{
		switch (Vector_of_Adjacent_elements.size())
		{
		case 5:
			if (Two_D_matrix[Vector_of_Adjacent_elements[0].first][Vector_of_Adjacent_elements[0].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[3].first][Vector_of_Adjacent_elements[3].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[0].first][Vector_of_Adjacent_elements[0].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[1].first][Vector_of_Adjacent_elements[1].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[3].first][Vector_of_Adjacent_elements[3].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[4].first][Vector_of_Adjacent_elements[4].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[1].first][Vector_of_Adjacent_elements[1].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[4].first][Vector_of_Adjacent_elements[4].second] == "S")
			{
				return true;
			}
			break;

		case 8:
			if (Two_D_matrix[Vector_of_Adjacent_elements[0].first][Vector_of_Adjacent_elements[0].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[7].first][Vector_of_Adjacent_elements[7].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[2].first][Vector_of_Adjacent_elements[2].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[5].first][Vector_of_Adjacent_elements[5].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[1].first][Vector_of_Adjacent_elements[1].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[6].first][Vector_of_Adjacent_elements[6].second] == "S")
			{
				return true;
			}
			else if (Two_D_matrix[Vector_of_Adjacent_elements[3].first][Vector_of_Adjacent_elements[3].second] == "S" && Two_D_matrix[Vector_of_Adjacent_elements[4].first][Vector_of_Adjacent_elements[4].second] == "S")
			{
				return true;
			}
			break;

		default:
			return false;
		}
	}*/
	bool O_scenerio_checker(vector<vector<string>> second_Two_D_matrix, int n, int m, int i, int j)    //in parameter (2d vector, height, width, index 1, index 2)
	{
		if (isValidPos(i - 1, j, n, m) == 1 && isValidPos(i - 1, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i - 1][j] == "S" && second_Two_D_matrix[i - 1][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j - 1, n, m) == 1 && isValidPos(i, j + 1, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i][j - 1] == "S" && second_Two_D_matrix[i][j + 1] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j - 1, n, m) == 1 && isValidPos(i + 1, j + 1, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i - 1][j - 1] == "S" && second_Two_D_matrix[i + 1][j + 1] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j - 1, n, m) == 1 && isValidPos(i - 1, j + 1, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "O" && second_Two_D_matrix[i + 1][j - 1] == "S" && second_Two_D_matrix[i - 1][j + 1] == "S")
			{
				return true;
			}
		}
	}

	bool S_scenerio_checker(vector<vector<string>> second_Two_D_matrix, int n, int m, int i, int j)    //in parameter (2d vector, height, width, index 1, index 2)
	{
		if (isValidPos(i + 1, j + 1, n, m) == 1 && isValidPos(i + 2, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j + 1] == "O" && second_Two_D_matrix[i + 2][j + 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j, n, m) == 1 && isValidPos(i + 2, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j] == "O" && second_Two_D_matrix[i + 2][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i + 1, j - 1, n, m) == 1 && isValidPos(i + 2, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i + 1][j - 1] == "O" && second_Two_D_matrix[i + 2][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j - 1, n, m) == 1 && isValidPos(i, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i][j - 1] == "O" && second_Two_D_matrix[i][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j - 1, n, m) == 1 && isValidPos(i - 2, j - 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j - 1] == "O" && second_Two_D_matrix[i - 2][j - 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j, n, m) == 1 && isValidPos(i - 2, j, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j] == "O" && second_Two_D_matrix[i - 2][j] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i - 1, j + 1, n, m) == 1 && isValidPos(i - 2, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i - 1][j + 1] == "O" && second_Two_D_matrix[i - 2][j + 2] == "S")
			{
				return true;
			}
		}
		if (isValidPos(i, j + 1, n, m) == 1 && isValidPos(i, j + 2, n, m) == 1)
		{
			if (second_Two_D_matrix[i][j] == "S" && second_Two_D_matrix[i][j + 1] == "O" && second_Two_D_matrix[i][j + 2] == "S")
			{
				return true;
			}
		}
	}
};


