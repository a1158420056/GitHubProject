// rapijXMLReadWrite.cpp : �������̨Ӧ�ó������ڵ㡣
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

	//��ӡ����XML����
	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//д���ļ�
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

	//��ӡ����XML����
	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//д���ļ�
	std::ofstream out("write_file2.xml");//ofstreamĬ��ʱ,����ļ������򸲸�ԭ��������,���������½�
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
	rapidxml::print(std::back_inserter(text), doc, 0);//doc���������textβ��
	std::cout << text << std::endl;

	xml_node<>* root = doc.first_node();
	xml_node<>* Devices = root->first_node();
	//xml_node<>* job = root->first_node("job");

	//�Ƴ����ڵ��µ�Devices����µ�MotherBoard�ڵ�
	xml_node<>* MotherBoard = Devices->first_node("MotherBoard");
	Devices->remove_node(MotherBoard);

	//
	text = "�Ƴ����ڵ��µ�Devices����µ�MotherBoard�ڵ�\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//��Devices��Graphics�ڵ㴦����һ��KeyBorad�ڵ�
	xml_node<>* Graphics = Devices->first_node("Graphics");//�ҵ�Graphics�ڵ�
	xml_node<>* new_node = doc.allocate_node(node_element, "KeyBorad", "Logitech");
	new_node->append_attribute(doc.allocate_attribute("Interface", "USB"));
	Devices->insert_node(Graphics, new_node);

	text = "��Devices�������һ��KeyBorad�ڵ�\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//�Ƴ����ڵ��µ�Devices���(�����ý�������н��)
	root->remove_node(Devices);
	text = "�Ƴ����ڵ��µ�Devices���(�����ý�������н��)\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//�Ƴ����ڵ������н��
	root->remove_all_nodes();
	text = "�Ƴ����ڵ������н��\r\n";
	rapidxml::print(std::back_inserter(text), doc, 0);
	std::cout << text << std::endl;

	//д���ļ�
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