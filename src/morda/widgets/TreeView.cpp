#include "TreeView.hpp"



using namespace morda;



TreeView::TreeView(const stob::Node* chain) :
		Widget(chain)
{
	this->list = ting::New<VerticalList>();
	this->Add(this->list);
	
	auto& lp = this->getLayoutParams(*this->list);
	
	lp.dim.y = Widget::LayoutParams::D_Max;
	lp.dim.x = Widget::LayoutParams::D_Min;
	
	
	
	
	
	Tree t;
	
	t.add(4);
	
	t.add(t.pos({0}), 1);
	
	t.add(t.pos({2}), 3);
	
	t.add(t.pos({2, 1}), 2);
	
	
	for(auto i = t.begin(); i != t.end(); ++i){
		for(auto s : i.path()){
			TRACE_ALWAYS(<< s << " ")
		}
		TRACE_ALWAYS(<< std::endl)
	}
	
	TRACE_ALWAYS(<< "total size = " << t.size() << std::endl)
	
}

void TreeView::setItemsProvider(std::shared_ptr<ItemsProvider> provider){
	this->list->setItemsProvider(
			std::shared_ptr<List::ItemsProvider>(
					static_cast<List::ItemsProvider*>(provider.get())
				)
		);
}

void TreeView::ItemsProvider::notifyDataSetChanged() {
	this->visibleItemsTree.reset();
	this->curIndex = 0;
	this->curPath.clear();
	this->List::ItemsProvider::notifyDataSetChanged();
}


size_t TreeView::ItemsProvider::count() const noexcept{
	if (this->visibleItemsTree.numUnderlyingVisible == 0) {
		ASSERT(this->visibleItemsTree.children.size() == 0)
		this->visibleItemsTree.init(this->count(ting::Buffer<size_t>()));
	}
	return this->visibleItemsTree.numUnderlyingVisible;
}


std::shared_ptr<Widget> TreeView::ItemsProvider::getWidget(size_t index) const {
	//TODO:
	return nullptr;
}

void TreeView::ItemsProvider::recycle(size_t index, std::shared_ptr<Widget> w) const {
	std::vector<size_t> path;
	
	//TODO:
}
