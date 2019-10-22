#include <RunzhongMachine/RunzhongMachine.hpp>

constexpr std::string_view lex_json = "../lexcial/src/report.json";
constexpr std::string_view syn_js = "../parse_tree/src/main_syn.js";
constexpr std::string_view layer_json = "../parse_tree/src/layer.json";

void invalid()
{
    std::cerr << "invalid command!!!\n";
}

void lex_viz()
{
    system("cd ../lexcial/ && unset HOST && npm start");
}

void syn_viz()
{
    system("cd ../parse_tree/ && unset HOST && npm start");
}

void viz_together()
{
    system("(cd ~/Desktop/runzhong_machine_compiler/lexcial/ && unset HOST && npm start && y) & (cd ~/Desktop/runzhong_machine_compiler/parse_tree/ && unset HOST && npm start && y)");
}

void help()
{
    std::cout << R"(MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMOc:oKMMMMMMMMMMMMMMKl::::::::cld0NMMMMMKo::::::::::::::oXMMM0l::ckWMMMMMOc:dXMMMKo:::::::cldONMMMM
MMo  .OMMMMMMMMMMMMMMk.   .....    ,kWMMM0;..........    '0MMMx.   .OMMMMMo  '0MMMk.   ....    'xNMM
MMo  .OMMMMMMMMMMMMMMk.  lKKKKKOd'  .xWMMWXKKKKKKKKKd.  .dNMMMx.    ,KMMMMo  '0MMMk.  lKKK0Oo'  .xMM
MMo  .OMMMMMMMMMMMMMMk.  dMMMMMMMO.  :NMMMMMMMMMMWNx.  'kWMMMMx.  .  :XMMMo  '0MMMk.  dMMMMMMx.  oWM
MMo  .OMMMMMMMMMMMMMMk.  dMMMMMMMO.  :NMMMMMMMMMNo'.  ;0MMMMMMx. .o;  lNMMo  '0MMMk.  lXNXX0x,  ,0MM
MMo  .OMMMMMMMMMMMMMMk.  lXXXXK0x,  .xWMMMMMMMMK:   .lXMMMMMMMk. .kO' .xWMo  '0MMMk.  ........;xXMMM
MMo  .OMMMMMMMMMMMMMMk.  .......   ,kWMMMMMMMW0,   .xWMMMMMMMMk. .kMk. .OWo  '0MMMk.  .,,,,,,'',cONM
MMo  .OMMMMMMMMMMMMMMk.  .;;;;.   lNMMMMMMMMWk.  ,oOWMMMMMMMMMx. .kMWd. ,Ko  '0MMMk.  oWWWWWNKo.  lN
MMo  .OMMMMMMMMMMMMMMk.  dMMMMO'  'OMMMMMMMNo.  :KMMMMMMMMMMMMk. .kMMNl  :c  '0MMMO.  dMMMMMMMWc  .O
MMo  .OMMMMMMMMMMMMMMk.  dMMMMWO.  'OMMMMMX:  .dNMMMMMMMMMMMMMk. .kMMMXc  .  '0MMMk.  dMMMMMMWk'  '0
MMo  .;llllllllllo0MMk.  dMMMMMWk.  'OWMMK;   ,oddodddddddKMMMk. .kMMMMK;    '0MMMk.  'lllllc,.  .dW
MMd.             .xMMk. .xMMMMMMWk.  ,OWMO'              .xMMMk. .kMMMMM0,   ;KMMMO'         ..,cOWM
MMN0OOOOOOOOOOOOO0NMMN0O0NMMMMMMMWKOOOXMMNKOOOOOOOOOOOOOO0NMMMN0O0NMMMMMMXOOOKWMMMN0OOOOOOOO00XWMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM)" << '\n';
    std::cout << "@@@[HELP]:\t\tlrznb help\n"
              << "@@@[LEXICAL]:\t\tlrznb ${your file} lexical\n"
              << "@@@[SYNTAX]:\t\tlrznb ${your file} syntax\n"
              << "@@@[LEXCIAL-VIZ]:\tlrznb ${your file} lexviz\n"
              << "@@@[SYNTAX-VIZ]:\tlrznb ${your file} synviz\n"
              << "@@@[GO]:\t\tlrznb ${your file} go\n";
    std::cout << ">>> Author -> ljw | ljy | zzz(nb) \n";
}

int main(int argc, const char** argv)
{
    if(argc == 2)
    {
        std::string_view com = argv[1];
        if(com != "help")
            invalid();
        help();
    } else if(argc == 3)
    {
        std::string_view fname = argv[1];

        auto src = rm::get_src(fname);
        auto ans = rm::lexical_analyze(src);

        std::string_view com_ = argv[2];
        rm::exporter exporter(ans);
        if(!rm::equal_any(com_, "lexcial", "syntax", "lexviz", "synviz", "go"))
        {
            invalid();
            help();
            std::exit(-1);
        }
        if(com_ == "lexcial" || com_ == "go")
            exporter.lexcial(lex_json);
        if(com_ == "syntax" || com_ == "go")
        {
            exporter.parse_root = rm::ll1_parse(ans);
            exporter.syntax(syn_js, src);
            std::ofstream lf(layer_json.data());
            lf << "{\n\t\"layer\":";
            lf << 15;
            lf << "\n}";
        }
        if(com_ == "lexviz")
            lex_viz();
        else if(com_ == "synviz")
            syn_viz();
        else if(com_ == "go")
            viz_together();
    } else
    {
        invalid();
        help();
    }
}