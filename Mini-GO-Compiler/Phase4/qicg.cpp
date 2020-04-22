
#include <bits/stdc++.h>



#define STR(VAR) (#VAR)
#define release 1
#define MAXCHILD 10
using namespace std;
struct SymbolTableTree{
	struct SymbolTableTree *child[MAXCHILD];
    string nodeType;
    string name;
    string value;
    string dataType;
    int lineNo;
    int Nchildren;
    int scope;
    int scopeChildren;
    struct SymbolTableTree *parent;
};
struct ast{
    int Nchildren;
    string str;
    ast *child[MAXCHILD];
};


//namespace ksb{
    // template<typename OP, typename ARG1, typename ARG2, typename RES>
    // class Quadruple
    // {

    // public:
    //     OP op;
    //     ARG1 arg1;
    //     ARG2 arg2;
    //     RES result;
    //     Quadruple(OP _op, ARG1 _arg1, ARG2 _arg2, RES _result): op(_op), arg1(_arg1), arg2(_agr2), result(_result){};
    // };

    unsigned int temp_counter = 0;
    unsigned int label_counter = 1;
    std::vector<std::string> stk1;
    std::vector<std::string> stk2;
    class Quadruple
    {

    public:
        std::string op;
        std::string arg1;
        std::string arg2;
        std::string result;
        Quadruple(std::string _op, std::string _arg1, std::string _arg2, std::string _result): op(_op), arg1(_arg1), arg2(_arg2), result(_result){};
    };
    void get_icg_rec(SymbolTableTree *, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper);
    std::string get_icg_for_exp(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper);
    void get_icg_for_var_def(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper);
    void get_icg_for_while(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper);
    void get_icg_for_switch_case(SymbolTableTree *node, std::vector<Quadruple> &icg, std::string &tmpv, std::string &label, std::map<string, SymbolTableTree> &mapper);
    void get_icg_for_switch(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper);
    void get_icg_for_printf(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper);


    SymbolTableTree *make_new_node(string nodeType, string name, string value, string dataType, int lineNo, SymbolTableTree *parent){
        SymbolTableTree *ttt = new SymbolTableTree;
        ttt -> nodeType = nodeType;
        ttt -> name = name;
        ttt -> value = value;
        ttt -> dataType = dataType;
        ttt -> lineNo = lineNo;
        ttt -> Nchildren = 0;
        ttt -> scope = -1;
        ttt -> scopeChildren = 0;
        ttt -> parent = parent;
        return ttt;
    }

    

    void get_icg_rec(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper){
        // cout<<"lol2\n";
        if(node->nodeType=="Expression"){
            // cout<<"lol3\n";
            get_icg_for_exp(node,icg, mapper);
        }
        else if(node->nodeType=="While"){
            // cout<<"lol4\n";
            get_icg_for_while(node,icg, mapper);
        }
        else if(node->nodeType=="Switch"){
            // cout<<"lol5\n";
            get_icg_for_switch(node,icg, mapper);
        }
        else if(node->nodeType=="VariableDefine"){
            // cout<<"lol6\n";
            get_icg_for_var_def(node,icg, mapper);
        }
        else if(node->nodeType=="Extra_SemiColon"){
            // cout<<"lol7\n";
            return;
        }
        else if(node->nodeType=="Scope2_Continue"){
            // cout<<"lol8\n";
            std::string tmp;
            if(stk1.size()>0) tmp = stk1.back();
            else tmp = stk2.back();
            Quadruple newg("goto", "", "", tmp);
            icg.push_back(newg);
            return;
        }
        else if(node->nodeType=="Scope2_Break"){
            // cout<<"lol9\n";
            Quadruple newg("goto", "", "", stk2.back());
            icg.push_back(newg);
            return;
        }
        else if(node->nodeType=="Main_Scope_Return"){
            // cout<<"lol10\n";
            Quadruple newg("goto", "", "", "l0");
            icg.push_back(newg);
            return;
        }
        else if(node->nodeType == "Print"){
            get_icg_for_printf(node,icg, mapper);
        }
        else{
            for(int i = 0; i < node -> Nchildren; ++i){
                get_icg_rec(node->child[i], icg, mapper);
            }
        }
        
    }

    void get_icg_for_print_inside(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper, int &p){
        if(node->nodeType == "PrintInsider"){
            std::string t1 = get_icg_for_exp(node -> child[2], icg, mapper);
            ++p;
            Quadruple newq("Param", t1, "", "");
            icg.push_back(newq);
            get_icg_for_print_inside(node -> child[0], icg, mapper, p);
            return;
        }
        std::string t1 = get_icg_for_exp(node, icg, mapper);
        ++p;
        Quadruple newq("Param", t1, "", "");
        icg.push_back(newq);
    }

    void get_icg_for_printf(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper){
        if(node->Nchildren == 4){
            Quadruple newq("Param", node->value, "", "");
            icg.push_back(newq);
            Quadruple newq2("call", "printf", "1", "");
            icg.push_back(newq2);
        }
        else {
            Quadruple newq("Param", node->value, "", "");
            icg.push_back(newq);
            int p = 1;
            get_icg_for_print_inside(node -> child[3], icg, mapper, p);
            Quadruple newq2("call", "printf", std::to_string(p), "");
            icg.push_back(newq2);
        }
    }

    std::string get_icg_for_exp(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper){
        // cout<<"lol14\n";
        // cout<<"lol15 "<<(node==nullptr)<<"\n";
        if(node -> nodeType == "Expression"){
            if(node->Nchildren > 2) return get_icg_for_exp(node -> child[1], icg, mapper);
            return get_icg_for_exp(node -> child[0], icg, mapper);
        }
        else if(node -> nodeType == "BinaryFOp" || node -> nodeType == "BinarySOp" || node -> nodeType == "RelationalOp" || node -> nodeType == "LogicalOp"){
            std::string t1 = "t"+std::to_string(temp_counter++);
            
            std::string t2 = get_icg_for_exp(node -> child[0], icg, mapper);
            std::string t3 = get_icg_for_exp(node -> child[2], icg, mapper);
            if(node -> nodeType == "RelationalOp" || node -> nodeType == "LogicalOp")   mapper[t1] = *make_new_node("TempVariable", t1, "", "int", -1, node);
            else mapper[t1] = *make_new_node("TempVariable", t1, "", mapper[t2].dataType, -1, node);
            Quadruple newq(node->child[1]->value, t2, t3, t1);
            icg.push_back(newq);
            return t1;
        }
        else if(node->nodeType == "Value"){
            // cout<<"lol15\n";
            std::string t1 = "t"+std::to_string(temp_counter++);
            mapper[t1] = *make_new_node("TempVariable", t1, node -> value, node->dataType, -1, node);
            Quadruple newq("=", node -> value, "", t1);
            icg.push_back(newq);
            return t1;
        }
        else if( node->nodeType == "Identifier" ){
            std::string t1 = "t"+std::to_string(temp_counter++);
            mapper[t1] = *make_new_node("TempVariable", t1, node -> value, node->dataType, -1, node);
            Quadruple newq("=", node -> name, "", t1);
            icg.push_back(newq);
            return t1;
        }
        else if( node->nodeType == "Unary" )
        {
            std::string t1 = "t"+std::to_string(temp_counter++);
            if(node -> child[0] -> nodeType == "BinaryFOp"){
                std::string t2 = get_icg_for_exp(node -> child[1], icg, mapper);
                Quadruple newq(node -> child[0] -> value, t2, "", t1);
                icg.push_back(newq);
                return t1;
            }
            if(node -> child[0] -> nodeType == "UnaryOp"){
                std::string t2 = get_icg_for_exp(node -> child[1], icg, mapper);
                if(node ->child[0] -> value == "--"){
                    Quadruple newq("-", t2, "1", node->child[1]->name);
                    icg.push_back(newq);

                    Quadruple newq2("=", node->child[1]->name, "", t1);
                    mapper[t1] = *make_new_node("TempVariable", t1, node ->child[1]-> value, node->child[1]->dataType, -1, node);
                    icg.push_back(newq2);
                }
                else{
                    Quadruple newq("+", t2, "1", node->child[1]->name);
                    icg.push_back(newq);

                    Quadruple newq2("=", node->child[1]->name, "", t1);
                    mapper[t1] = *make_new_node("TempVariable", t1, node ->child[1]-> value, node->child[1]->dataType, -1, node);
                    icg.push_back(newq2);
                }

                return t1;
            }
            std::string t2 = get_icg_for_exp(node -> child[0], icg, mapper);
            if(node ->child[1] -> value == "--"){
                Quadruple newq2("=", node->child[0]->name, "", t1);
                mapper[t1] = *make_new_node("TempVariable", t1, node ->child[0]-> value, node->child[0]->dataType, -1, node);
                icg.push_back(newq2);

                Quadruple newq("-", t2, "1", node->child[0]->name);
                icg.push_back(newq);
            }
            else{
                Quadruple newq2("=", node->child[0]->name, "", t1);
                mapper[t1] = *make_new_node("TempVariable", t1, node ->child[0]-> value, node->child[0]->dataType, -1, node);
                icg.push_back(newq2);

                Quadruple newq("+", t2, "1", node->child[0]->name);
                icg.push_back(newq);
            }
            return t1;
        }

        else if(node -> nodeType == "Assign"){
            std::string t1 = "t"+std::to_string(temp_counter++);
            std::string t2 = get_icg_for_exp(node->child[2], icg, mapper);
            Quadruple newq2("=", t2, "", node->child[0]->name);
            icg.push_back(newq2);
            Quadruple newq3("=", node->child[0]->name, "", t1);
            icg.push_back(newq3);
            mapper[t1] = *make_new_node("TempVariable", t1, node -> child[0]->value, node->child[0]->dataType, -1, node);
            return t1;
        }

        return "";
        
    }

    void get_icg_for_var_def(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper){
        if (node->Nchildren == 3 && node -> child[0]-> nodeType == "TypeName"){
            // cout<<"lol11\n";
            // cout<<(node->Nchildren)<<"\n";
            get_icg_for_var_def(node->child[1], icg, mapper);
            // cout<<"lol100\n";
            return;
        }
        if(node->Nchildren == 3){
            if(node->child[1]->nodeType=="Comma"){
                get_icg_for_var_def(node->child[2], icg, mapper);
                return;
            }
            // cout<<"lol12\n";
            std::string tmpv = get_icg_for_exp(node -> child[2], icg, mapper);
            Quadruple newq("=", tmpv, "", node->child[0]->name);
            icg.push_back(newq);
        }
        else if(node->Nchildren == 5){
            std::string tmpv = get_icg_for_exp(node -> child[2], icg, mapper);
            Quadruple newq("=", tmpv, "", node->child[0]->name);
            icg.push_back(newq);
            get_icg_for_var_def(node->child[4], icg, mapper);
        }
        // cout<<"lol200\n";
    }

    void get_icg_for_while(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper){
        std::string tmpv = get_icg_for_exp(node -> child[0] -> child[2], icg, mapper);
        auto l1 = "l"+std::to_string(label_counter++);
        auto l2 = "l"+std::to_string(label_counter++);
        stk1.push_back(l1);
        stk2.push_back(l2);
        Quadruple newl("Lable", "", "", l1);
        Quadruple newq("ifFalse", tmpv, "", l2);
        icg.push_back(newl);
        icg.push_back(newq);
        if(node -> Nchildren == 2) {get_icg_rec(node->child[1], icg, mapper);
            Quadruple newg("goto", "", "", l1);
            icg.push_back(newg);
        }"l"+std::to_string(label_counter++);
        Quadruple newl2("Lable", "", "", l2);
        icg.push_back(newl2);
        stk1.pop_back();
        stk2.pop_back();
    }

    void get_icg_for_switch_case(SymbolTableTree *node, std::vector<Quadruple> &icg, std::string &tmpv, std::string &label, std::map<string, SymbolTableTree> &mapper){
        if(node -> Nchildren < 2) return;
        if(node -> child[0] -> Nchildren > 2){
            std::string tmpv2 = get_icg_for_exp(node -> child[0] -> child[1], icg, mapper);
            std::string tmpv3 = "t"+std::to_string(temp_counter++);
            auto l1 = "l"+std::to_string(label_counter++);
            auto l2 = "l"+std::to_string(label_counter++);
            Quadruple newc("==", tmpv2, tmpv, tmpv3);
            icg.push_back(newc);
            Quadruple newq("ifFalse", tmpv3, "", l1);
            icg.push_back(newq);
            if(label.length() > 1){
                Quadruple newl("Lable", "", "", label);
                icg.push_back(newl);
            }
            get_icg_rec(node->child[1], icg, mapper);
            Quadruple newg("goto", "", "", l2);
            icg.push_back(newg);
            Quadruple newl("Lable", "", "", l1);
            icg.push_back(newl);
            get_icg_for_switch_case(node -> child[2], icg, tmpv, l2, mapper);
            return;
        }
        if(label.length() > 1){
            Quadruple newl("Lable", "", "", label);
            icg.push_back(newl);
        }
        get_icg_rec(node->child[1], icg, mapper);
        std::string l2 = stk2.back();
        Quadruple newg("goto", "", "", l2);
        icg.push_back(newg);
        get_icg_for_switch_case(node -> child[2], icg, tmpv, l2, mapper);
    }

    void get_icg_for_switch(SymbolTableTree *node, std::vector<Quadruple> &icg, std::map<string, SymbolTableTree> &mapper){
        std::string tmpv = get_icg_for_exp(node -> child[0] -> child[2], icg, mapper);
        auto l2 = "l"+std::to_string(label_counter++);
        stk2.push_back(l2);
        std::string tmplabel = "";
        get_icg_for_switch_case(node->child[2], icg, tmpv, tmplabel, mapper);
        Quadruple newl2("Lable", "", "", l2);
        icg.push_back(newl2);
        stk2.pop_back();
    }

    std::vector<Quadruple> &get_icg(SymbolTableTree *node, std::map<string, SymbolTableTree> &mapper){
        std::vector<Quadruple> *icg = new std::vector<Quadruple>;
        // cout<<"\n\n\nlol0\n";
        get_icg_rec(node, *icg, mapper);
        // cout<<"lol1\n";
        Quadruple newl2("Lable", "", "", "l0");
        icg->push_back(newl2);
        return *icg;
    }
    
//}