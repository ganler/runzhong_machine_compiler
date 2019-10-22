/**
 * @author Fine
 * @description Topographic Map
 */
import React from 'react';
import TreeMap from './components/TreeMap';
import data from './main_syn';
//import data from './report.json';
import './App.css';

class App extends React.Component {
    
  info = {
    data: data,
    width: 1000,
    height: 800,
  }

  render() {
    return (
      <div className="App">
        <h1 className="App-header">
          RunZhong Machine
          语法分析树
        </h1>
      <TreeMap {...this.info} />
      </div>
    );
  }
}

export default App;
