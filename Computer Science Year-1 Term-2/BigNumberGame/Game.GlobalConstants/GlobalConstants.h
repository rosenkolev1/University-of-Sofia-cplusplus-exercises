#pragma once

#include "..\Project.StringManipulation\MString.h"

class GlobalConstants
{
public:
	// INTERNAL CONSTANTS
	static const mstring BAD_ALLOC_EXCEPTION;
	static const mstring PLACEHOLDER;

	//---UI AND TEXT OUTPUT CONSTANTS
	//------NOT LOGGED/GLOBAL
	static const mstring WELCOME_STARTSCREEN_TEXT;
	static const mstring BUTTON_START;
	static const mstring BUTTON_END;
	static const mstring GAME_END;
	static const mstring COMMAND_INVALID;
	static const mstring RETURN_TEXT;
	static const mstring USER_DOES_NOT_EXIST;

	//------PLACEHOLDERS
	static const mstring USERNAME_PLACEHOLDER;
	static const mstring EXPRESSION_PLACEHOLDER;
	static const mstring LEVEL_PLACEHOLDER;
	static const mstring LIVES_PLACEHOLDER;
	static const mstring SOLUTION_PLACEHOLDER;
	static const mstring HIGHSCORE_PLACEHOLDER;

	//------LOGIN/REGISTER
	static const mstring LOGIN_OR_REGISTER;
	static const mstring REGISTER;
	static const mstring REGISTER_SUCCESS;
	static const mstring REGISTER_USERNAME_TAKEN;
	static const mstring LOGIN;
	static const mstring LOGIN_USERNAME_TAKEN;

	//------LOGGED_MAINMENU
	static const mstring MAINMENU_LOGGED_STARTGAME;
	static const mstring MAINMENU_LOGGED_CONTINUEGAME;
	static const mstring MAINMENU_LOGGED_RESTARTGAME;
	static const mstring MAINMENU_LOGGED_RETURN_TEXT;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS;
	static const mstring MAINMENU_LEVEL_TEXT;
	static const mstring MAINMENU_LIVES_TEXT;
	static const mstring MAINMENU_HIGHSCORE_TEXT;
	static const mstring MAINMENU_HIGHSCORE_NEW;

	//------ADMIN_MAINMENU
	static const mstring ADMIN_GETINFO;
	static const mstring ADMIN_GETINFO_ALL;
	static const mstring ADMIN_GETINFO_DOESNOTEXIST;
	static const mstring ADMIN_GETINFO_SINGLE_HEADER;
	static const mstring ADMIN_GETINFO_MANY_HEADER;

	static const mstring ADMIN_DELETEACCOUNT;
	static const mstring ADMIN_DELETEACCOUNT_CONFIRMATION;
	static const mstring ADMIN_DELETEACCOUNT_CONFIRMATION_YES;
	static const mstring ADMIN_DELETEACCOUNT_CONFIRMATION_NO;
	static const mstring ADMIN_DELETEACCOUNT_SUCCESS;
	static const mstring ADMIN_DELETEACCOUNT_ALREADY_DELETED;
	static const mstring ADMIN_DELETEACCOUNT_DELETEADMIN_NOTALLOWED;

	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD;
	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION;
	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION_YES;
	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION_NO;
	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD_SUCCESS;
	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD_ALREADYEXCLUDED;
	 
	static const mstring ADMIN_INCLUDEINLEADERBOARD;
	static const mstring ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION;
	static const mstring ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION_YES;
	static const mstring ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION_NO;
	static const mstring ADMIN_INCLUDEINLEADERBOARD_SUCCESS;
	static const mstring ADMIN_INCLUDEINLEADERBOARD_ALREADYINCLUDED;
	static const mstring ADMIN_INCLUDEINLEADERBOARD_INCLUDEADMIN_NOTALLOWED;

	static const mstring ADMIN_ADDHELPER;


	static const mstring ADMIN_RECOVER;
	static const mstring ADMIN_RECOVER_CONFIRMATION;
	static const mstring ADMIN_RECOVER_CONFIRMATION_YES;
	static const mstring ADMIN_RECOVER_CONFIRMATION_NO;
	static const mstring ADMIN_RECOVER_SUCCESS;
	static const mstring ADMIN_RECOVER_NOTBANNED;
	static const mstring ADMIN_RECOVER_BANREASON;

	static const mstring ADMIN_LOGGEDASADMIN_TEXT;

	//------PLAYING INSIDE LEVEL
	static const int PLAYING_LIVES_DEFAULT;
	static const mstring PLAYING_LIVES_TEXT;
	static const mstring PLAYING_LEVEL_TEXT;
	static const mstring PLAYING_EXPRESSION_SOLVE;
	static const mstring PLAYING_EXPRESSION;
	static const mstring PLAYING_HELPERS;
	static const mstring PLAYING_SOLUTION_ENTER;
	static const mstring PLAYING_RETURN_TEXT;
	static const mstring PLAYING_CHEATCODE_GETSOLUTION;
	static const mstring PLAYING_CORRECT;
	static const mstring PLAYING_WRONG_TRYAGAIN;
	static const mstring PLAYING_WRONG_GAMEOVER;
	static const mstring PLAYING_GAMEOVER_NEWHIGHSCORE;
	static const mstring PLAYING_GAMEOVER_RESTART;
	static const mstring PLAYING_GAMEOVER_RETURN_TO_MAINMENU;
	static const mstring PLAYING_STARTING_GAME;
	static const mstring PLAYING_CONTINUE_GAME;
	static const mstring PLAYING_RESTART_GAME;

	//------SCREEN TITLES
	static const mstring STARTSCREEN_TITLE;
	static const mstring LOGINORREGISTER_TITLE;
	static const mstring REGISTER_TITLE;
	static const mstring LOGIN_TITLE;
	static const mstring MAINMENU_TITLE;
	static const mstring DELETE_CONFIRM_TITLE;
	static const mstring RECOVER_CONFIRM_TITLE;
	static const mstring EXCLUDEFROMLEADERBOARD_CONFIRM_TITLE;
	static const mstring INCLUDEINLEADERBOARD_CONFIRM_TITLE;
	static const mstring BIGNUMBER_GAME_TITLE;
	static const mstring GAMEOVER_TITLE;

	//---COMMAND INPUT CONSTANTS
	static const mstring COMMAND_TRUE;
	static const mstring COMMAND_FALSE;
	static const mstring COMMAND_TRUE_SHORT;
	static const mstring COMMAND_FALSE_SHORT;

	static const mstring COMMAND_MAINMENU_START;
	static const mstring COMMAND_MAINMENU_END;
	static const mstring COMMAND_RETURN;

	static const mstring COMMAND_LOGIN_START;
	static const mstring COMMAND_REGISTER_START;
	static const char COMMAND_DELIM;

	static const mstring COMMAND_GAME_START;
	static const mstring COMMAND_GAME_CONTINUE;
	static const mstring COMMAND_GAME_RESTART;

	static const mstring COMMAND_ACCOUNT_DELETE;
	static const mstring COMMAND_ACCOUNT_DELETE_CONFIRM;

	static const mstring COMMAND_ACCOUNT_RECOVER_CONFIRM;
	static const mstring COMMAND_ADMIN_RECOVER;

	static const mstring COMMAND_ADMIN_GETINFO;
	static const mstring COMMAND_ADMIN_GETINFO_PARAM_DELETEDONLY;
	static const mstring COMMAND_ADMIN_DELETE;
	static const mstring COMMAND_ADMIN_ADD;

	static const mstring COMMAND_ADMIN_EXCLUDE;
	static const mstring COMMAND_ADMIN_INCLUDE;
	static const mstring COMMAND_ADMIN_EXCLUDE_CONFIRM;
	static const mstring COMMAND_ADMIN_INCLUDE_CONFIRM;

	static const mstring COMMAND_PLAYING_CHEATCODE_GETSOLUTION;
};

