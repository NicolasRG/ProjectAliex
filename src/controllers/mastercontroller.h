/**
 * This Logic Layer will hold the parent state of the game. 
 * Properties meant for this to hanlde
 * - high level steam info
 *    - player name, steam avatar
 * - save states
 * - parent confgurations 
 *     - load controller specs?
 *     - language details
 *     - any global preferences
 * - what game app state : MAIN_MENU, LOBBY, IN-MULTI-GAME, IN-SINGLE-GAME 
 */
#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H
#include <mutex>

/*
	The purpose of this abstraciton layer is to decouple
	the godot logic/callbacks/signals api out of the game logic.
	It also allows this to be a pure singlton
*/
namespace controller{
	class MasterController
	{

		/**
		 * The Singleton's constructor/destructor should always be private to
		 * prevent direct construction/desctruction calls with the `new`/`delete`
		 * operator.
		 */
	private:
		static MasterController * pinstance_;
		static std::mutex mutex_;
		bool is_connected_to_steam = false;

	protected:
		MasterController() {}
		~MasterController() {}

	public:
		/**
		 * Singletons should not be cloneable.
		 */
		MasterController(MasterController &other) = delete;
		/**
		 * Singletons should not be assignable.
		 */
		void operator=(const MasterController &) = delete;
		/**
		 * This is the static method that controls the access to the singleton
		 * instance. On the first run, it creates a singleton object and places it
		 * into the static field. On subsequent runs, it returns the client existing
		 * object stored in the static field.
		 */

		static MasterController *GetInstance();
		/**
		 * Finally, any singleton should define some business logic, which can be
		 * executed on its instance.
		 */
		void init(bool is_editor);
		bool get_is_connected_to_steam();
	};
}
#endif