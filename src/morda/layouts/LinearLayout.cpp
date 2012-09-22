#include "LinearLayout.hpp"

#include <ting/Array.hpp>



using namespace morda;



LinearLayout::LinearLayout(const stob::Node& description){
	if(const stob::Node* n = description.GetProperty("orientation")){
		if(n->Value() == "horizontal"){
			this->isVertical = false;
		}else{
			this->isVertical = true;
		}
	}else{
		this->isVertical = true;
	}
}



//override
void LinearLayout::ArrangeWidgets(Container& cont)const{
//	unsigned longIndex, transIndex;
//	if(this->isVertical){
//		longIndex = 1;
//		transIndex = 0;
//	}else{
//		longIndex = 0;
//		transIndex = 1;
//	}
	
	//calculate net weight
	float netWeight = 0;
	
	ting::Array<float> weights(cont.NumChildren());
	
	{
		float *i = weights.Begin();
		for(const ting::Ref<Widget>* c = &cont.Children(); *c; c = &(*c)->Next(), ++i){
			const stob::Node* layout = Layout::GetLayoutProp(**c);
			ASSERT(weights.Overlaps(i))
			if(!layout){
				*i = 0;
				continue;
			}
			if(const stob::Node* weight = layout->GetProperty("weight")){
				*i = weight->AsFloat();
				netWeight += *i;
			}else{
				*i = 0;
			}
		}
	}
	
	
	//TODO:
}



//override
morda::Vec2f LinearLayout::ComputeMinDim(const Container& cont)const throw(){
	morda::Vec2f minDim(0);
	
	unsigned longIndex, transIndex;
	if(this->isVertical){
		longIndex = 1;
		transIndex = 0;
	}else{
		longIndex = 0;
		transIndex = 1;
	}
	
	for(const ting::Ref<const Widget>* c = &cont.Children(); *c; c = &(*c)->Next()){
		const morda::Vec2f& md = (*c)->GetMinDim();
		if(minDim[transIndex] < md[transIndex]){
			minDim[transIndex] = md[transIndex];
		}
		minDim[longIndex] =+ md[longIndex];
	}
	return minDim;
}
