//
// Created by lmauro on 5/9/16.
//

#include <tinyxml2.h>

namespace tinyxml2
{

void DeepClone(XMLNode *newNode,
               const XMLNode *nodeSrc,
               XMLDocument *DocDest,
               const XMLNode *)
{
    const XMLNode *child = nodeSrc->FirstChild();
    if (child) {
        XMLNode *newNode2 = child->ShallowClone(DocDest);
        DeepClone(newNode2, child, DocDest, nodeSrc);
        newNode->InsertFirstChild(newNode2);
        for (; ;) {
            XMLNode *lastClone = newNode2;
            const XMLNode *child2 = child->NextSibling();
            if (!child2) {
                break;
            }

            newNode2 = child2->ShallowClone(DocDest);
            DeepClone(newNode2, child2, DocDest, nodeSrc);
            newNode->InsertAfterChild(lastClone, newNode2);
            child = child2;
        }
    }
}

}
