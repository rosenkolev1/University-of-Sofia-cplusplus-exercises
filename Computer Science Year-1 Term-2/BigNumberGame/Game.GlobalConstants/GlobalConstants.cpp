#include "GlobalConstants.h"

// INTERNAL CONSTANTS
const mstring GlobalConstants::BAD_ALLOC_EXCEPTION = "Bad allocation of memory";
const mstring GlobalConstants::PLACEHOLDER = "LOREM IPSUM TEXT";

//---UI AND TEXT OUTPUT CONSTANTS
//------NOT LOGGED/GLOBAL
const mstring GlobalConstants::WELCOME_STARTSCREEN_TEXT = "Welcome to the BigNumber game!!!\nHere, you will be forced to answer some equations with BigNumbers in them. Enjoy!\n\n";
const mstring GlobalConstants::BUTTON_START = "START GAME(start)\n";
const mstring GlobalConstants::BUTTON_END = "END GAME(end)\n";
const mstring GlobalConstants::GAME_END = "GAME HAS ENDED!!!\nTHANK YOU FOR PLAYING";
const mstring GlobalConstants::COMMAND_INVALID = "INVALID COMMAND! TRY AGAIN\n";
const mstring GlobalConstants::RETURN_TEXT = "\n\nRETURN TO PREVIOUS SCREEN(r)";
const mstring GlobalConstants::USER_DOES_NOT_EXIST = "Error! This user doesn't exist!";

const mstring GlobalConstants::BUTTON_LEADERBOARD = "\nLEADERBOARD(lb)\n\n";
const mstring GlobalConstants::BUTTON_LEADERBOARD_ADMIN = "\nLEADERBOARD({lb/lb|(getDeleted: {f}/{false}/{t}/{true}/{deletedOnly})|(getExcluded: {exc}/{inc}) )\n";
const mstring GlobalConstants::LEADERBOARD_TEXT = "\nLEADERBOARD:\n";
const mstring GlobalConstants::LEADERBOARD_USER_TEXT = ". {username} --> {highscore}";
const int GlobalConstants::LEADERBOARD_COLS_COUNT = 3;
const mstring GlobalConstants::LEADERBOARD_COLS[3]
{
	"Position",
	"Username",
	"Highscore"
};

//------PLACEHOLDERS
const mstring GlobalConstants::USERNAME_PLACEHOLDER = "{username}";
const mstring GlobalConstants::EXPRESSION_PLACEHOLDER = "{expression}";
const mstring GlobalConstants::LEVEL_PLACEHOLDER = "{level}";
const mstring GlobalConstants::LIVES_PLACEHOLDER = "{lives}";
const mstring GlobalConstants::SOLUTION_PLACEHOLDER = "{solution}";
const mstring GlobalConstants::HIGHSCORE_PLACEHOLDER = "{highscore}";

//------LOGIN/REGISTER
const mstring GlobalConstants::USERNAME_OR_PASSWORD_INVALID = "\nError! The username or password is invalid! Check that you meet the criteria above for validity of the username or password!\n";
const mstring GlobalConstants::LOGIN_OR_REGISTER = "Choose one of the following:\n\nLOGIN(log)\n\nREGISTER(reg)";
const mstring GlobalConstants::REGISTER = "Enter your username and password ({username} | {password})\nUsername is between 6 and 100 characters!\nPassword is between 6 and 100 characters!\nWhitespaces are not allowed!\n'|' character is not allowed as part of the username or password!";
const mstring GlobalConstants::REGISTER_SUCCESS = "\nSuccessfully registered user!\n";
const mstring GlobalConstants::REGISTER_USERNAME_TAKEN = "\nThis username has already been taken! Sorry brother.\n";
const mstring GlobalConstants::LOGIN = "Enter your username and password ({username} | {password}).";
const mstring GlobalConstants::LOGIN_USER_DOESNOTEXIST = "\nError! This user doesn't exist! Password or username is wrong!\n";

//------LOGGED_MAINMENU
const mstring GlobalConstants::MAINMENU_LOGGED_STARTGAME = "\nSTART GAME(s)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_CONTINUEGAME = "\nCONTINUE GAME(c)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_RESTARTGAME = "\nRESTART GAME(restart)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT ACCOUNT(r)";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT = "DELETE YOUR OWN ACCOUNT(delete)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION = "\nWARNING: THIS ACTION WILL DELETE YOUR ACCOUNT FOREVER. PROCEED ANYWAY?\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES = "\nDELETE ACCOUNT(delete_account)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS = "\nACCOUNT DELETION WAS SUCCESSFUL\n";
const mstring GlobalConstants::MAINMENU_LEVEL_TEXT = "Current Level: ";
const mstring GlobalConstants::MAINMENU_LIVES_TEXT = "Lives: ";
const mstring GlobalConstants::MAINMENU_HIGHSCORE_TEXT = "Highscore: ";
const mstring GlobalConstants::MAINMENU_HIGHSCORE_NEW = "\n!!!NEW HIGHSCORE ACHIEVED!!!\n";

//------ADMIN_MAINMENU
const mstring GlobalConstants::ADMIN_GETINFO = "\nGET INFO ABOUT ACCOUNT(getinfo|{username})\n";
const mstring GlobalConstants::ADMIN_GETINFO_ALL = "\nGET INFO ABOUT ACCOUNTS(getinfo|all|(getDeleted: {f}/{false}/{t}/{true}/{deletedOnly}) )\n";
const mstring GlobalConstants::ADMIN_GETINFO_DOESNOTEXIST = "{username} DOES NOT EXIST!";
const mstring GlobalConstants::ADMIN_GETINFO_SINGLE_HEADER = "\nUser info:\n";
const mstring GlobalConstants::ADMIN_GETINFO_MANY_HEADER = "\nUsers info:\n";

const mstring GlobalConstants::ADMIN_DELETEACCOUNT = "\nDELETE ACCOUNT(delete|{message}|{account name})\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION = "\nWARNING: THIS ACTION WILL DELETE {username}'s ACCOUNT. PROCEED ANYWAY?\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION_YES = "\nDELETE ACCOUNT(delete_account)\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_SUCCESS = "\n{username}'s ACCOUNT DELETION WAS SUCCESSFUL\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_ALREADY_DELETED = "{username}'s ACCOUNT HAS ALREADY BEEN DELETED!";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_DELETEADMIN_NOTALLOWED = "THIS ACCOUNT IS AN ADMIN ACCOUNT WHICH CANNOT BE DELETED!";

const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD = "\nEXCLUDE FROM LEADERBOARD(exclude|{account name})\n";
const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION = "\nWARNING: THIS ACTION WILL EXCLUDE {username} FROM HIGHSCORE LEADERBOARD. PROCEED ANYWAY?\n";
const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION_YES = "\nEXCLUDE ACCOUNT(exclude_account)\n";
const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_SUCCESS = "\n{username}'s ACCOUNT EXCLUSION FROM LEADERBOARDS WAS SUCCESSFUL\n";
const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_ALREADYEXCLUDED = "{username}'s ACCOUNT HAS ALREADY BEEN EXCLUDED!";

const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD = "\nINCLUDE FROM LEADERBOARD(include|{account name})\n";
const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION = "\nWARNING: THIS ACTION WILL INCLUDE {username} IN THE HIGHSCORE LEADERBOARD. PROCEED ANYWAY?\n";
const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION_YES = "\nINCLUDE ACCOUNT(include_account)\n";
const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_SUCCESS = "\n{username}'s ACCOUNT INCLUSION IN LEADERBOARDS WAS SUCCESSFUL\n";
const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_ALREADYINCLUDED = "{username}'s ACCOUNT IS ALREADY INCLUDED!";
const mstring GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_INCLUDEADMIN_NOTALLOWED = "THIS ACCOUNT IS AN ADMIN ACCOUNT WHICH CANNOT BE INCLUDED!";

const mstring GlobalConstants::ADMIN_ADDHELPER = "\nADD HELPER(add|{helper name})\n";

const mstring GlobalConstants::ADMIN_RECOVER = "\nRECOVER ACCOUNT(recover|{helper name})\n";
const mstring GlobalConstants::ADMIN_RECOVER_CONFIRMATION = "\nWARNING: THIS ACTION WILL RECOVER {username}'s ACCOUNT. PROCEED ANYWAY?\n";
const mstring GlobalConstants::ADMIN_RECOVER_BANREASON = "\nREASON FOR BAN:\n";
const mstring GlobalConstants::ADMIN_RECOVER_CONFIRMATION_YES = "\nRECOVER ACCOUNT(recover_account)\n";
const mstring GlobalConstants::ADMIN_RECOVER_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::ADMIN_RECOVER_SUCCESS = "\n{username}'s ACCOUNT RECOVERED SUCCESSFULLY\n";
const mstring GlobalConstants::ADMIN_RECOVER_NOTBANNED = "{username}'s ACCOUNT IS NOT BANNED!";

const mstring GlobalConstants::ADMIN_LOGGEDASADMIN_TEXT = "\n!!!LOGGED AS ADMIN!!!\n";

//------PLAYING INSIDE LEVEL
const int GlobalConstants::PLAYING_LIVES_DEFAULT = 3;
const mstring GlobalConstants::PLAYING_LEVEL_TEXT = "Current Level: {level}\n";
const mstring GlobalConstants::PLAYING_LIVES_TEXT = "Lives: {lives}\n";
const mstring GlobalConstants::PLAYING_EXPRESSION_SOLVE = "\nSolve the equation:\n";
const mstring GlobalConstants::PLAYING_EXPRESSION = "\n{expression}\n\n";
const mstring GlobalConstants::PLAYING_HELPERS = "Helpers: \n";
const mstring GlobalConstants::PLAYING_SOLUTION_ENTER = "\nENTER THE SOLUTION. THE DIGITS OF THE NUMBER CAN BE SEPERATED BY COMMAS FOR EASIER READABILITY\n";
const mstring GlobalConstants::PLAYING_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT THIS LEVEL(r)! PROGRESS WILL BE SAVED AUTOMATICALLY";
const mstring GlobalConstants::PLAYING_SOLUTION_ENTER_COMMAND_TEXT = "\nEnter solution: ";
const mstring GlobalConstants::PLAYING_CHEATCODE_GETSOLUTION = "The solution is: {solution}";
const mstring GlobalConstants::PLAYING_CORRECT = "\nYou have entered the correct answer, well done!\n";
const mstring GlobalConstants::PLAYING_WRONG_TRYAGAIN = "\nYour answer is incorrect. You have lost 1 life. Try again!\n";
const mstring GlobalConstants::PLAYING_WRONG_GAMEOVER = "YOUR ANSWER IS INCORRECT.\nYOU HAVE 0 LIVES LEFT!\n";
const mstring GlobalConstants::PLAYING_GAMEOVER_NEWHIGHSCORE = "\n...BUT YOU HAVE ACHIEVED A NEW HIGHSCORE OF {highscore}! CONGRATULATIONS!\n";
const mstring GlobalConstants::PLAYING_GAMEOVER_RESTART = "\nRESTART FROM THE BEGINNING({s, restart})\n";
const mstring GlobalConstants::PLAYING_GAMEOVER_RETURN_TO_MAINMENU = "\nRETURN TO MAIN MENU(r)\n";
const mstring GlobalConstants::PLAYING_STARTING_GAME = "\nStarting Game...";
const mstring GlobalConstants::PLAYING_CONTINUE_GAME = "\nContinueing Game...";
const mstring GlobalConstants::PLAYING_RESTART_GAME = "\nRestarting Game...";

//------SCREEN TITLES
const mstring GlobalConstants::STARTSCREEN_TITLE = "START UP SCREEN";
const mstring GlobalConstants::LOGINORREGISTER_TITLE = "LOGIN OR REGISTER SCREEN";
const mstring GlobalConstants::REGISTER_TITLE = "REGISTER SCREEN";
const mstring GlobalConstants::LOGIN_TITLE = "LOGIN SCREEN";
const mstring GlobalConstants::MAINMENU_TITLE = "MAIN MENU SCREEN";
const mstring GlobalConstants::DELETE_CONFIRM_TITLE = "DELETE ACCOUNT SCREEN";
const mstring GlobalConstants::RECOVER_CONFIRM_TITLE = "RECOVER ACCOUNT SCREEN";
const mstring GlobalConstants::EXCLUDEFROMLEADERBOARD_CONFIRM_TITLE = "EXCLUDE FROM LEADERBOARD SCREEN";
const mstring GlobalConstants::INCLUDEINLEADERBOARD_CONFIRM_TITLE = "INCLUDE IN LEADERBOARD SCREEN";
const mstring GlobalConstants::BIGNUMBER_GAME_TITLE = "BIGNUMBER GAME SCREEN";
const mstring GlobalConstants::GAMEOVER_TITLE = "GAMEOVER SCREEN";

//---COMMAND INPUT CONSTANTS
const mstring GlobalConstants::COMMAND_TRUE = "true";
const mstring GlobalConstants::COMMAND_FALSE = "false";
const mstring GlobalConstants::COMMAND_TRUE_SHORT = "t";
const mstring GlobalConstants::COMMAND_FALSE_SHORT = "f";

const mstring GlobalConstants::COMMAND_MAINMENU_START = "start";
const mstring GlobalConstants::COMMAND_MAINMENU_END = "end";
const mstring GlobalConstants::COMMAND_LEADERBOARD = "lb";
const mstring GlobalConstants::COMMAND_RETURN = "r";

const mstring GlobalConstants::COMMAND_LOGIN_START = "log";
const mstring GlobalConstants::COMMAND_REGISTER_START = "reg";
const char GlobalConstants::COMMAND_DELIM = '|';

const mstring GlobalConstants::COMMAND_GAME_START = "s";
const mstring GlobalConstants::COMMAND_GAME_CONTINUE = "c";
const mstring GlobalConstants::COMMAND_GAME_RESTART = "restart";

const mstring GlobalConstants::COMMAND_LEADERBOARD_GETEXCLUDED = "exc";
const mstring GlobalConstants::COMMAND_LEADERBOARD_GETINCLUDED = "inc";

const mstring GlobalConstants::COMMAND_ACCOUNT_DELETE = "delete";
const mstring GlobalConstants::COMMAND_ACCOUNT_DELETE_CONFIRM = "delete_account";

const mstring GlobalConstants::COMMAND_ADMIN_RECOVER = "recover";
const mstring GlobalConstants::COMMAND_ACCOUNT_RECOVER_CONFIRM = "recover_account";

const mstring GlobalConstants::COMMAND_ADMIN_GETINFO = "getinfo";
const mstring GlobalConstants::COMMAND_ADMIN_PARAM_DELETEDONLY = "deletedOnly";
const mstring GlobalConstants::COMMAND_ADMIN_DELETE = "delete";
const mstring GlobalConstants::COMMAND_ADMIN_ADD = "add";

const mstring GlobalConstants::COMMAND_ADMIN_EXCLUDE = "exclude";
const mstring GlobalConstants::COMMAND_ADMIN_INCLUDE = "include";
const mstring GlobalConstants::COMMAND_ADMIN_EXCLUDE_CONFIRM = "exclude_account";
const mstring GlobalConstants::COMMAND_ADMIN_INCLUDE_CONFIRM = "include_account";

const mstring GlobalConstants::COMMAND_PLAYING_CHEATCODE_GETSOLUTION = "gsl";