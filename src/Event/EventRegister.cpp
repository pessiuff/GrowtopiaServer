#include <Event/EventPool.hpp>

/*

████████╗███████╗██╗  ██╗████████╗    ███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
╚══██╔══╝██╔════╝╚██╗██╔╝╚══██╔══╝    ██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
   ██║   █████╗   ╚███╔╝    ██║       █████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
   ██║   ██╔══╝   ██╔██╗    ██║       ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
   ██║   ███████╗██╔╝ ██╗   ██║       ███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
   ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝       ╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/
#include <Event/TextEvents/RequestedName.hpp>
#include <Event/TextEvents/TankIDName.hpp>
#include <Event/TextEvents/Action.hpp>

#include <Event/TextEvents/Actions/OnDialogReturn.hpp>
#include <Event/TextEvents/Actions/EnterGame.hpp>
#include <Event/TextEvents/Actions/Quit.hpp>
#include <Event/TextEvents/Actions/RefreshItemData.hpp>
#include <Event/TextEvents/Actions/RefreshPlayerTributeData.hpp>
#include <Event/TextEvents/Actions/JoinRequest.hpp>
#include <Event/TextEvents/Actions/QuitToExit.hpp>

#include <Event/Dialogs/AccountDialog.hpp>

#include <Event/Tank/OnMovement.hpp>