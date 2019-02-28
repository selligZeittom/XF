#include "xf/nulltransition.h"

XFNullTransition::XFNullTransition(interface::XFReactive *pBehavior) : XFEvent(XFEventType::NullTransition, 0, pBehavior)
{

}

XFNullTransition::~XFNullTransition()
{

}

bool XFNullTransition::deleteAfterConsume() const
{
    return false;
}
