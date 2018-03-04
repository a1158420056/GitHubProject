// rapidXMLReadTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

using namespace rapidxml;

int main()
{
	file<> fdoc("config.xml");
	std::cout << fdoc.data() << std::endl;
	xml_document<>   doc;
	doc.parse<0>(fdoc.data());

	std::cout << doc.name() << std::endl;

	//! ��ȡ���ڵ�
	xml_node<>* root = doc.first_node();
	std::cout << root->name() << std::endl;

	//! ��ȡ���ڵ��һ���ڵ�
	xml_node<>* node1 = root->first_node();
	std::cout << node1->name() << std::endl;

	xml_node<>* node11 = node1->first_node();
	std::cout << node11->name() << std::endl;
	std::cout << node11->value() << std::endl;
	
	for (auto it = node1->first_node(); it != NULL; it=it->next_sibling())
	{
		std::cout << it->name() << ":" << it->value() << std::endl;
	}

	//! ���֮���ٴα���
	//��Ҫ˵������rapidxml������һ��bug
	//�Ǿ���append_node(doc.allocate_node(node_element,"h","0"));��ʱ�򲢲����Ǹö����Ƿ����!
	xml_node<>* size = root->first_node("size");
	size->append_node(doc.allocate_node(node_element, "w", "5"));
	size->append_node(doc.allocate_node(node_element, "h", "8"));

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	std::cout << text << std::endl;

	std::ofstream out("config.xml");
	out << doc;

	system("PAUSE");
	return EXIT_SUCCESS;
}
