// rapijXMLReadWrite.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tchar.h>
#include <string>
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>//rapidxml::file
#include <rapidxml_print.hpp>//rapidxml::print
using namespace rapidxml;

//
void WriteFile1()
{
	xml_document<> doc;
	xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(rot);

	xml_node<>* config = doc.allocate_node(node_element, "config", "information");
	doc.append_node(config);

	xml_node<>* color = doc.allocate_node(node_element, "color", NULL);
	color->append_node(doc.allocate_node(node_element, "red", "88"));
	color->append_node(doc.allocate_node(node_element, "green", "108"));
	color->append_node(doc.allocate_node(node_element, "blue", "128"));
	color->append_node(doc.allocate_node(node_element, "alpha", "255"));
	config->append_node(color);

	xml_node<>* size = doc.allocate_node(node_element, "size", NULL);
	size->append_node(doc.allocate_node(node_element, "x", "1024"));
	size->append_node(doc.allocate_node(node_element, "y", "768"));
	config->append_node(size);

	xml_node<>* mode = doc.allocate_node(rapidxml::node_element, "mode", "screen mode");
	mode->append_attribute(doc.allocate_attribute("fullscreen", "false"));
	config->append_node(mode);

	//打印整个XML内容
	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//写入文件
	std::ofstream out("write_file1.xml");
	out << doc;
	out.close();

	/*<?xml version="1.0" encoding="utf-8" ?>
	<config>
	<color>
	<red>88</red>
	<green>108</green>
	<blue>128</blue>
	<alpha>255</alpha>
	</color>
	<size>
	<x>1024</x>
	<y>768</y>
	</size>
	<mode fullscreen="false">screen mode</mode>
	</config>*/
}
//
void WriteFile2()
{
	xml_document<> doc;
	char strbuf[] =
		/*"<?xml version=\'1.0\' encoding=\'utf-8\' ?>"*/
		"<root>"
		"<Devices>"
		"<Monitor>LG</Monitor>"
		"<MotherBoard>Gigabyte</MotherBoard>"
		"<MemoryBar>Kingston</MemoryBar>"
		"<Graphics>MSI</Graphics>"
		"<Hardisk>WD</Hardisk>"
		"</Devices>"

		"<job>"
		"<name>CSDN</name>"
		"<website>http://blog.csdn.net/hellokandy</website>"
		"<addr>Guangzhou China</addr>"
		"</job>"
		"</root>";
	doc.parse<0>(strbuf);

	//打印整个XML内容
	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//写入文件
	std::ofstream out("write_file2.xml");//ofstream默认时,如果文件存在则覆盖原来的内容,不存在则新建
	out << doc;
	out.close();
}
//
void ModifyFile()
{
	//
	file<> fdoc("write_file2.xml");
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);//doc内容输出到text尾处
	std::cout << text << std::endl;

	xml_node<>* root = doc.first_node();
	xml_node<>* Devices = root->first_node();
	//xml_node<>* job = root->first_node("job");

	//移除根节点下的Devices结点下的MotherBoard节点
	xml_node<>* MotherBoard = Devices->first_node("MotherBoard");
	Devices->remove_node(MotherBoard);

	//
	text = "移除根节点下的Devices结点下的MotherBoard节点\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//在Devices的Graphics节点处插入一个KeyBorad节点
	xml_node<>* Graphics = Devices->first_node("Graphics");//找到Graphics节点
	xml_node<>* new_node = doc.allocate_node(node_element, "KeyBorad", "Logitech");
	new_node->append_attribute(doc.allocate_attribute("Interface", "USB"));
	Devices->insert_node(Graphics, new_node);

	text = "在Devices下面插入一个KeyBorad节点\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//移除根节点下的Devices结点(包括该结点下所有结点)
	root->remove_node(Devices);
	text = "移除根节点下的Devices结点(包括该结点下所有结点)\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//移除根节点下所有结点
	root->remove_all_nodes();
	text = "移除根节点下所有结点\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//写入文件
	std::ofstream out("write_file2_delete.xml");
	out << doc;
	out.close();
}
//
int _tmain(int argc, _TCHAR* argv[])
{
	//
	WriteFile1();

	//
	WriteFile2();

	//
	ModifyFile();

	system("pause");
	return 0;
}