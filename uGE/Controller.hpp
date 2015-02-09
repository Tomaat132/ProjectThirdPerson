#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace uGE {

	class GameObject;
	class Controller
	{
		protected:
			GameObject * _parent;

		public:
			Controller( GameObject * parent );
			virtual ~Controller();

			virtual void update() = 0; // abstract function need for override
	};
}
#endif // CONTROLLER_H
