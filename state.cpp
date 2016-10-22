#include "state.h"

CState::CState(): iSteps(0), pparent(NULL) {}

void CState::checkSomeFields(const CState &) const {}

CState::~CState() {}
