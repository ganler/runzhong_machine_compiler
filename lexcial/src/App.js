import React from 'react';
import './App.css';

const Component = React.Component

//const startOutput = ["It", "was", "the", "best", "of", "times,", "it", "was", "the", "worst", "of", "times,", "it", "was", "the", "age", "of", "wisdom,", "it", "was", "the", "age", "of", "foolishness,", "it", "was", "the", "epoch", "of", "belief,", "it", "was", "the", "epoch", "of", "incredulity,", "it", "was", "the", "season", "of", "Light,", "it", "was", "the", "season", "of", "Darkness,", "it", "was", "the", "spring", "of", "hope,", "it", "was", "the", "winter", "of", "despair,", "we", "had", "everything", "before", "us,", "we", "had", "nothing", "before", "us,", "we", "were", "all", "going", "direct", "to", "Heaven,", "we", "were", "all", "going", "direct", "the", "other", "way-", "in", "short,", "the", "period", "was", "so", "far", "like", "the", "present", "period,", "that", "some", "of", "its", "noisiest", "authorities", "insisted", "on", "its", "being", "received,", "for", "good", "or", "for", "evil,", "in", "the", "superlative", "degree", "of", "comparison", "only."];
const startOutput = [["Input"],["source"],["code"]];

//const startInput = "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way- in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only."

const srcPlaceholder = "Input src code";

var line_cnt=0;
var char_cnt=0;
var json_cnt=0;

function getJsonLength(jsonData){
    var jsonLength = 0;
    for(var item in jsonData){
       jsonLength++;
    }
    return jsonLength;
}    

function changeColor(item) {
    if(typeof(item) == "undefined")
    {
        return "#3f3f3f";
    }
    console.log("item: "+item+"  json_cnt: "+json_cnt);
    const reportInfos = require('./report.json');
    const tokenInfos = require('./token.json');
    var jsonlength = getJsonLength(reportInfos.report);
    //console.log(jsonlength);//项数
    var line;
    if(item == '\n')
    {
        line_cnt++;
        char_cnt = 0;
        //console.log("line_cnt: "+ line_cnt);
        //console.log("nnn json_cnt:"+json_cnt+"char_cnt: "+char_cnt+"  item:"+item);
        return "#ffffff";
    }
    if(item != null)
    {
        if(char_cnt == reportInfos.report[json_cnt].pos && line_cnt == reportInfos.report[json_cnt].line)
        {
            var type = reportInfos.report[json_cnt].type;
            //console.log("token:"+tokenInfos.color[type].code);
            char_cnt++;
            json_cnt++;
            //console.log("match json_cnt:"+json_cnt+"char_cnt: "+char_cnt+"  item:"+item);
            return tokenInfos.color[type].code;
        }
        else
        {
            var comment = 11;
            char_cnt++;
            //console.log("unmatch json_cnt:"+json_cnt+"char_cnt: "+char_cnt+"  item:"+item);
            return tokenInfos.color[comment].code;
        }
    }   
    for(var i=0;i<jsonlength;i++) {
        //read json data
        line = reportInfos.report[i].line;
        type = reportInfos.report[i].type;
        
    }
}

function assignColor(item) {
  var randomColor = require('randomcolor');   
  item = item.replace(/[^A-Za-z0-9]/g, "");
  //console.log(item);
    return randomColor({
        luminosity: "light",
        seed: item.toLowerCase()
    });
}

class Previewer extends Component {
    constructor(props) {
        super(props);
        this.state = {            
            outputStr: startOutput,
            input_value: null,
            soluStr: null,
        }
        
        this.handleInput = this.handleInput.bind(this);
    }
    handleInput(event) {
        var val = event.target.value.match(/^.*.[\s\.\!\?]$/);
        var str = val[0].split(" ");
        var colors = [];
        for (let word of str) {
            var highlight = assignColor(word);
            colors.push(highlight);
        }
        this.setState({
            outputStr: str
        });
        console.log(str);
    }
    inputChange(val){
        //获取用户输入内容
        //console.log(val)//这是对象
        //console.log(val.target.value)//这是输入框内容文本
        //使用setsatte方法改变类中属性
        var strContent=val.target.value;
        //console.log("处理前的strContent为\r\n"+strContent);
        //strContent = strContent.replace(/\r\n/g, '<br/>'); //IE9、FF、chrome
		//strContent = strContent.replace(/\n/g, '<br/>'); //IE7-8
		//strContent = strContent.replace(/\s/g, '&nbsp;'); //空格处理
        //console.log("转换之后的html代码为\r\n"+strContent);
        line_cnt=0;
        char_cnt=0;
        json_cnt=0;
        //2维字符串数组
        var singleStr = strContent.split("");
        //console.log("singleStr"+singleStr);
        this.setState({
            input_value: val.target.value,
            outputStr: singleStr,//val.target.value.split(""),
        })
        
    }
    render() {
        return ( <div className="App">
            <div className="App-header">
                <h2>
                RunZhong Machine
                </h2>
            </div>
            
            <div className="App-div" >
                <textarea type="text" className="App-srcinput"
                placeholder = {
                    srcPlaceholder
                }
                value={this.state.input_value} onChange={this.inputChange.bind(this)}/>
            </div>
            <div className="App-div">
            <code> {                
                    this.state.outputStr.map((item) =>
                    <span style = {
                        {
                            //backgroundColor: assignColor(item)
                            color: changeColor(item)
                        }
                    }
                    className = "App-span" > {
                            item                     
                    } </span> 
                )
            } </code>
            </div>
            </div>
        )
    }
}
/*
ReactDOM.render( <Previewer/> ,
    document.getElementById("app")
);
*/

export default Previewer;
