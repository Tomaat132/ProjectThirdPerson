#ifndef VIKING_H
#define VIKING_H

namespace uGE {

    class Viking
    {
        public:
            Viking();
            virtual ~Viking();

            void vikingBuried();
        protected:
        private:
            static int alive;
    };
}
#endif // VIKING_H
