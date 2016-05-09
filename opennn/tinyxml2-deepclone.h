//
// Add DeepClone function to the tinyxml2 namespace.
//
// Created by lmauro on 5/9/16.
//

#ifndef OPENNN_TINYXML2_DEEPCLONE_H
#define OPENNN_TINYXML2_DEEPCLONE_H

namespace tinyxml2 {

    void DeepClone(tinyxml2::XMLNode *,
                   const tinyxml2::XMLNode *,
                   tinyxml2::XMLDocument *,
                   const tinyxml2::XMLNode *);

}

#endif //OPENNN_TINYXML2_DEEPCLONE_H
