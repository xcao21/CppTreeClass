/* 

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
	xinlincao AT gmail DOT com
*/

#include <algorithm>
#include <string>
#include <iostream>
#include "tree.hpp"
#include <cassert>

using namespace std;
using namespace general_tree;

void print_tree(tree<string>& tr)
{
	//print all children using preorder
	//top.skip_children(true);
	tree<string>::pre_order_iterator pre_iter = tr.root(); //tr.begin_pre_order_iterator();
	cout<<"------------pre_order_iterator print tree------------"<<endl;
	for(; pre_iter!=tr.end_pre_order_iterator(tr.root());++pre_iter)
	{
		//get depth
		cout<<"+";
		for(int i=0;i<tr.depth(pre_iter);i++) cout<<"+";
		cout<<*pre_iter<<endl;
	}
	cout<<"-----------pre_order_iterator print tree----------"<<endl;
}



void test_tree()
{
	//test head
	tree<string> tr;
	tree<string>::pre_order_iterator pos;
	bool b_is_valid_pos;
	b_is_valid_pos = tr.is_valid(pos);
	assert(!b_is_valid_pos);
	pos = tr.root();
	b_is_valid_pos = tr.is_valid(pos);
	assert(!b_is_valid_pos);
	b_is_valid_pos = tr.is_valid(tr.root());
	assert(!b_is_valid_pos);
	pos = tr.set_root("a");//insert
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	pos=tr.root();//get root
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	std::string str = pos.node->data;
	assert(str == string("a"));

	//append child
	tree<string>::pre_order_iterator pos_b1=tr.append_child(tr.root(), "b1");
	b_is_valid_pos = tr.is_valid(pos_b1);assert(b_is_valid_pos);
	str = pos_b1.node->data;
	assert(str == string("b1"));

	tree<string>::pre_order_iterator pos_c1=tr.append_child(pos_b1, "c1");
	b_is_valid_pos = tr.is_valid(pos_c1);assert(b_is_valid_pos);
	str = pos_c1.node->data;
	assert(str == string("c1"));

	tree<string>::pre_order_iterator pos_c2=tr.append_child(pos_b1, "c2");
	b_is_valid_pos = tr.is_valid(pos_c2);assert(b_is_valid_pos);
	str = pos_c2.node->data;
	assert(str == string("c2"));

	tree<string>::pre_order_iterator pos_d1=tr.append_child(pos_c1, "d1");
	b_is_valid_pos = tr.is_valid(pos_d1);assert(b_is_valid_pos);
	str = pos_d1.node->data;
	assert(str == string("d1"));

	tree<string>::pre_order_iterator pos_d2=tr.append_child(pos_c1, "d2");
	b_is_valid_pos = tr.is_valid(pos_d2);assert(b_is_valid_pos);
	str = pos_d2.node->data;
	assert(str == string("d2"));

	tree<string>::pre_order_iterator pos_b2=tr.append_child(tr.root(),"b2");
	b_is_valid_pos = tr.is_valid(pos_b2);assert(b_is_valid_pos);
	str = pos_b2.node->data;
	assert(str == string("b2"));

	tree<string>::pre_order_iterator pos_c3=tr.append_child(pos_b2, "c3");
	b_is_valid_pos = tr.is_valid(pos_c3);assert(b_is_valid_pos);
	str = pos_c3.node->data;
	assert(str == string("c3"));

	tree<string>::pre_order_iterator pos_c4=tr.append_child(pos_b2, "c4");
	b_is_valid_pos = tr.is_valid(pos_c4);assert(b_is_valid_pos);
	str = pos_c4.node->data;
	assert(str == string("c4"));
	
	cout<<"append child test:\n";
	print_tree(tr);

	//test reparent
	pos = tr.reparent_root("new_root");
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	str = pos.node->data;
	assert(str == string("new_root"));
	cout<<"reprarent new root test:\n";
	print_tree(tr);

	//test STL algorithm
	pos_d2 =std::find(tr.begin_pre_order_iterator(tr.root()), tr.end_pre_order_iterator(tr.root()), "d2");
	assert(pos_d2 != tr.end_pre_order_iterator(tr.root()));
	str = pos_d2.node->data;	assert(str == string("d2"));
    
	//insert before/after
	pos = tr.insert_after(pos_d2, "d4");
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	str = pos.node->data;	assert(str == string("d4"));

	pos = tr.insert_before(pos, "d3");
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	str = pos.node->data;	assert(str == string("d3"));
	cout<<"insert before/after test, d1,d2,d3,d4/c1\n";
	print_tree(tr);

	//move after/before
	pos_c4 =std::find(tr.begin_pre_order_iterator(tr.root()), tr.end_pre_order_iterator(tr.root()), "c3");
	assert(pos_c3 != tr.end_pre_order_iterator(tr.root()));
	pos_c1 =std::find(tr.begin_pre_order_iterator(tr.root()), tr.end_pre_order_iterator(tr.root()), "c1");
	assert(pos_c1 != tr.end_pre_order_iterator(tr.root()));

	pos = tr.move_after(pos_c3,pos_c1);
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	str = pos.node->data;
	assert(str == string("c1"));
	cout<<"move after/before test, c1(...)  c4\n";
	print_tree(tr);


	pos_c2 =std::find(tr.begin_pre_order_iterator(tr.root()), tr.end_pre_order_iterator(tr.root()), "c2");
	assert(pos_c2 != tr.end_pre_order_iterator(tr.root()));

	pos = tr.move_before(pos_c2,pos);
	b_is_valid_pos = tr.is_valid(pos);assert(b_is_valid_pos);
	str = pos.node->data;
	assert(str == string("c1"));
	cout<<"move after/before test, c1(...)  c2\n";
	print_tree(tr);


	//test operator=
	tree<string> atree,btree;
	atree = btree = tr;
	cout<<"test copy function and operator=\n";
	print_tree(atree);

	//test maxdepth
	int depth = atree.max_depth(atree.root());


	//test breadth first iterator
	cout<<"\nbread first visit root1:"<<endl;
	str.clear();
	tree<string>::breadth_first_queued_iterator bfsiter = tr.begin_breadth_first_iterator(tr.begin_pre_order_iterator(tr.root()));
	for(; bfsiter != tr.end_breadth_first_iterator(tr.begin_pre_order_iterator(tr.root())); ++ bfsiter)
	{
		//cout<<*bfsiter<<" ";
		str+=*bfsiter;str+=" ";
	}
	assert(str == std::string("new_root a b1 b2 c1 c2 c3 c4 d1 d2 d3 d4 "));
	cout<<str<<endl;

	str.clear();
	cout<<"\nbread first visit root2:"<<endl;
	bfsiter = tr.begin_breadth_first_iterator(tr.root());
	for(; bfsiter != tr.end_breadth_first_iterator(tr.root()); ++ bfsiter)
	{
		//cout<<*bfsiter<<" ";
		str+=*bfsiter;str+=" ";
	}
	assert(str == std::string("new_root a b1 b2 c1 c2 c3 c4 d1 d2 d3 d4 "));
	cout<<str<<endl;

	cout<<"\nbread first visit c1:"<<endl;
	pos_c1 =std::find(tr.begin_pre_order_iterator(tr.root()), tr.end_pre_order_iterator(tr.root()), "c1");
	assert(pos_c1 != tr.end_pre_order_iterator(tr.root()));
	str.clear();
	bfsiter = tr.begin_breadth_first_iterator(pos_c1);
	for(; bfsiter != tr.end_breadth_first_iterator(pos_c1); ++ bfsiter)
	{
		str+=*bfsiter;str+=" ";
	}
	assert(str == std::string("c1 d1 d2 d3 d4 "));
	cout<<str<<endl;

	//test preorder iterator
	cout<<"\n preorder first visit root1:"<<endl;
	str.clear();
	tree<string>::pre_order_iterator preorderIter = tr.begin_pre_order_iterator(tr.root());
	for(; preorderIter != tr.end_pre_order_iterator(tr.root()); ++ preorderIter)
	{
		str+=*preorderIter;str+=" ";
	}
	assert(str == std::string("new_root a b1 c1 d1 d2 d3 d4 c2 b2 c3 c4 "));
	cout<<str<<endl;

	cout<<"\n preorder first visit c1:"<<endl;
	str.clear();
	preorderIter = tr.begin_pre_order_iterator(pos_c1);
	for(; preorderIter != tr.end_pre_order_iterator(pos_c1); ++ preorderIter)
	{
		str+=*preorderIter;str+=" ";
	}
	assert(str == std::string("c1 d1 d2 d3 d4 "));
	cout<<str<<endl;

	//test postorder iterator
	cout<<"\n postorder first visit root1:"<<endl;
	str.clear();
	tree<string>::post_order_iterator postorderIter = tr.begin_post_order_iterator(tr.root());
	for(; postorderIter != tr.end_post_order_iterator(tr.root()); ++ postorderIter)
	{
		str+=*postorderIter;str+=" ";
	}
	assert(str == std::string("d1 d2 d3 d4 c1 c2 b1 c3 c4 b2 a new_root "));
	cout<<str<<endl;

	cout<<"\n postorder first visit c1:"<<endl;
	str.clear();
	postorderIter = tr.begin_post_order_iterator(pos_c1);
	for(; postorderIter != tr.end_post_order_iterator(pos_c1); ++ postorderIter)
	{
		str+=*postorderIter;str+=" ";
	} 
	assert(str == std::string("d1 d2 d3 d4 c1 "));
	cout<<str<<endl;


	//children test
	cout<<"\n children test visit root:"<<endl;
	str.clear();
	tree<string>::children_iterator child_pos = tr.begin_children_iterator(tr.root());
	for(int i =0 ; child_pos!=tr.end_children_iterator(tr.root());++child_pos,i++)
	{
		str+=*child_pos;str+=" ";
	}
	assert(str == std::string("a "));
	cout<<str<<endl;

	cout<<"\n children test visit c1:"<<endl;
	str.clear();
	tree<string>::children_iterator child_pos2 = tr.begin_children_iterator(pos_c1);
	for(int i =0 ; child_pos2!=tr.end_children_iterator(pos_c1);++child_pos2,i++)
	{
		str+=*child_pos2;str+=" ";
	}
	assert(str == std::string("d1 d2 d3 d4 "));
	cout<<str<<endl;


	//test leaf iterator
	cout<<"\n test leaf iterator of root:"<<endl;
	str.clear();
	tree<string>::leaf_iterator leaf_pos = tr.begin_leaf_iterator(tr.root());
	for(int i =0 ; leaf_pos!=tr.end_leaf_iterator(tr.root());++leaf_pos,i++)
	{
		str+=*leaf_pos;str+=" ";
	}
	assert(str == std::string("d1 d2 d3 d4 c2 c3 c4 "));
	cout<<str<<endl;

	cout<<"\n test leaf iterator of c1:"<<endl;
	str.clear();
	tree<string>::leaf_iterator leaf_pos2 = tr.begin_leaf_iterator(pos_c1);
	for(int i =0 ; leaf_pos2!=tr.end_leaf_iterator(pos_c1);++leaf_pos2,i++)
	{
		str+=*leaf_pos2;str+=" ";
	}
	assert(str == std::string("d1 d2 d3 d4 "));
	cout<<str<<endl;


	cout<<"test children and breadth first visit :"<<endl;
	child_pos= tr.begin_children_iterator(tr.root());
	for(int i =0 ; child_pos!=tr.end_children_iterator(tr.root());++child_pos,i++)
	{
		cout<<"# "<<i<<" child of top is "<< (*child_pos) <<" ";
		cout<<"it's breadth's members ";
		tree<string>::breadth_first_queued_iterator inner_bfsiter = tr.begin_breadth_first_iterator(child_pos);
		for(; inner_bfsiter != tr.end_breadth_first_iterator(child_pos); ++ inner_bfsiter)
		{
			cout<<*inner_bfsiter<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	//iterator conversion test
	{
		tree<string>::children_iterator tmp_pos1;
		tree<string>::pre_order_iterator tmp_pos2;
		tree<string>::post_order_iterator tmp_pos3;
		tree<string>::leaf_iterator tmp_pos4;
		tree<string>::breadth_first_queued_iterator tmp_pos5;
		//tmp_pos1 = tmp_pos3; //compilation error
		//tmp_pos2 = tmp_pos5; //compilation error
		//test copied preorder iterator
		cout<<"\n copied preorder first visit root1:"<<endl;
		str.clear();
		preorderIter = pos_c1;
		for(; preorderIter != tr.end_pre_order_iterator(pos_c1); ++ preorderIter)
		{
			str+=*preorderIter;str+=" ";
		}
		assert(str == std::string("c1 d1 d2 d3 d4 "));
		cout<<str<<endl;
	}


	//test STL search algorithms
	{
		tree<string>::children_iterator tmp_pos1 = std::find( tr.begin_children_iterator(tr.root()), tr.end_children_iterator(tr.root()),"c1");
		assert(tmp_pos1 == tr.end_children_iterator(tr.root()));
		tmp_pos1 = std::find( tr.begin_children_iterator(pos_c1), tr.end_children_iterator(pos_c1),"d2");
		assert(tmp_pos1 != tr.end_children_iterator(pos_c1));assert(*tmp_pos1 == string("d2"));

		tree<string>::pre_order_iterator tmp_pos2  = std::find( tr.begin_pre_order_iterator(tr.root()), tr.end_pre_order_iterator(tr.root()),"c1");
		assert(tmp_pos2 != tr.end_pre_order_iterator(tr.root()));assert(*tmp_pos2 == string("c1"));
		tree<string>::post_order_iterator tmp_pos3 = std::find( tr.begin_post_order_iterator(tr.root()), tr.end_post_order_iterator(tr.root()),"c1");
		assert(tmp_pos3 != tr.end_post_order_iterator(tr.root()));assert(*tmp_pos3 == string("c1"));
		tree<string>::leaf_iterator tmp_pos4 = std::find( tr.begin_leaf_iterator(tr.root()), tr.end_leaf_iterator(tr.root()),"d4");;
		assert(tmp_pos4 != tr.end_leaf_iterator(tr.root()));assert(*tmp_pos4 == string("d4"));
		tree<string>::breadth_first_queued_iterator tmp_pos5 = std::find( tr.begin_breadth_first_iterator(tr.root()), tr.end_breadth_first_iterator(tr.root()),"c1");
		assert(tmp_pos5 != tr.end_breadth_first_iterator(tr.root()));
	}


	
	tree<string>::children_iterator tmp_child_pos = tr.begin_children_iterator(pos_c1);
	for(int i =0 ; tmp_child_pos!=tr.end_children_iterator(pos_c1);++tmp_child_pos,i++)
	{
			cout<<*tmp_child_pos<<" ";
	}

	print_tree(tr);

	//get root
	//top = tr.begin_pre_order_iterator(tr.root());
	//get parent
	tree<string>::pre_order_iterator parentOfRoot = tr.parent(tr.root());
	if(NULL == parentOfRoot.node)
	{
		cout<<"root has no parent!"<<endl;
	}
	//get children number
	cout<<"the root has "<<tr.number_of_children(tr.root())<<" children"<<endl;



	//the first child of top
	if(tr.root().number_of_children()>0)
	{
	}

	//get every child using number of children
	for(int i=0; i<tr.root().number_of_children();i++)
	{
		//	cout<<"# "<<i<<" child of top is "<< *tr.child(top,i) <<" "<<endl;
	}

	//get every siblings
	tree<string>::children_iterator sib= tr.begin_children_iterator(tr.root());
	for(int i =0 ; sib!=tr.end_children_iterator(tr.root());++sib,i++)
	{
		//cout<<"# "<<i<<" child of top is "<< (*sib) <<" "<<endl;
	}
	cout<<endl;
    
	tree<string>::children_iterator sibIter= tr.begin_children_iterator(tr.root());
	for(int i =0 ; sibIter!=tr.end_children_iterator(tr.root());++sibIter,i++)
	{
		cout<<"# "<<i<<" child of "<< *tr.parent(sibIter) <<" is "<< (*sibIter) <<" "<<endl;
	}


}


int main(int argc, char* argv[], char* envp[])
{
	int nRetCode = 0;
    
    
	test_tree();
    
	return nRetCode;
}