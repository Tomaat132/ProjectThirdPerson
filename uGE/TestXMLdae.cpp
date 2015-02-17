#include "TestXMLdae.hpp"

#include "utils/tinyxml2.h"

namespace uGE{


    TestXMLdae::TestXMLdae()
    {
            //ctor
    }

    TestXMLdae::~TestXMLdae()
    {
           //dtor
    }
    //other stuff
    void dump_data(){
        tinyxml2::TiXmlDocument doc ("Assets/Level/test_export.dae");
        doc.LoadFile();
    }//end of void dump_data
}
