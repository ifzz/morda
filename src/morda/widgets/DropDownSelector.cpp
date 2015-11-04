#include "DropDownSelector.hpp"


using namespace morda;



namespace{

const char* DLayout = R"qwertyuiop(
		Label{
			name{morda_dropdown_selection}
			layout{
				dimX{0} dimY{min}
				weight{1}
			}
			text{stuff}
		}
		PushButton{
			Label{
				text{\/}
			}
		}
	)qwertyuiop";

}


DropDownSelector::DropDownSelector(const stob::Node* chain) :
		Widget(chain),
		HorizontalContainer(stob::parse(DLayout).get())
{
	
}