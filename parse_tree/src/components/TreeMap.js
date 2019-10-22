/**
 * @author Fine
 * @description tree map
 */
import React from 'react';
import * as d3 from 'd3';
import { Icon } from 'antd';
import CONSTANT from '../utils/CONSTANT';
import TreeComponent from './TreeComponent';
import '../App.css'

class TreeMap extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      currentNode: {}, // select node
      menuStatus: 'hidden',
      positionY: 0,
      positionX: 0,
      tranInfo: CONSTANT.TRANINFO,
      isFullScreen: false,
      dataSource: null,
    }
  }

  componentDidMount() {
    this.watchFullScreen();
    this.setState({dataSource: this.props.data});
  }

  nodeClick(event, currentNode) {
    event.stopPropagation();
    const positionX = event.pageX + CONSTANT.DIFF.X + 'px';
    const positionY = event.pageY + CONSTANT.DIFF.Y  + 'px';

    this.setState({menuStatus: 'visible', currentNode, positionX, positionY});
  }

  cancleActive = () => {
    // reset node active
    this.setState({menuStatus: 'hidden', currentNode: {}});
  }

  nodeClick = (event, currentNode) => {
    const positionX = event.pageX + CONSTANT.DIFF.X + 'px';
    const positionY = event.pageY + CONSTANT.DIFF.Y  + 'px';

    event.stopPropagation();
    this.setState({menuStatus: 'visible', currentNode, positionX, positionY});
  }

  zoomIn = () => {
    const g = d3.select('.tree_map');
    d3.zoom().scaleBy(g, 0.9);
    const tranInfo = d3.zoomTransform(g.node());
    this.setState({tranInfo});
  }

  zoomOut = () => {
    const g = d3.select('.tree_map');
    d3.zoom().scaleBy(g, 1.1);
    const tranInfo = d3.zoomTransform(g.node());
    this.setState({tranInfo});
  }

  viewFullPage = () => {
    if (this.state.isFullScreen) {
      this.exitFullscreen();
    } else {
      this.requestFullScreen();
    }
  }

  requestFullScreen() {
    const de = document.documentElement;
    if (de.requestFullscreen) {
      de.requestFullscreen();
    } else if (de.mozRequestFullScreen) {
      de.mozRequestFullScreen();
    } else if (de.webkitRequestFullScreen) {
      de.webkitRequestFullScreen();
    }
  }

  // exit full screen
  exitFullscreen() {
    if (document.exitFullscreen) {
      document.exitFullscreen();
    } else if (document.mozCancelFullScreen) {
      document.mozCancelFullScreen();
    } else if (document.webkitCancelFullScreen) {
      document.webkitCancelFullScreen();
    }
  }

  watchFullScreen() {
    document.addEventListener(
      "fullscreenchange",
      () => {
        this.setState({
          isFullScreen: document.fullscreen
        });
      },
      false
    );
    document.addEventListener(
      "mozfullscreenchange",
      () => {
        this.setState({
          isFullScreen: document.mozFullScreen
        });
      },
      false
    );
    document.addEventListener(
      "webkitfullscreenchange",
      () => {
        this.setState({
          isFullScreen: document.webkitIsFullScreen
        });
      },
      false
    );
  }

  render() {
    const {
      currentNode, positionX, positionY,
      menuStatus, tranInfo, isFullScreen, dataSource
    } = this.state;

    return (
      <div classname = "map" >
      <div onClick={this.cancleActive}>
        <TreeComponent {...this.props} tranInfo={tranInfo} nodeClick={this.nodeClick}
          dataSource={dataSource} currentNode={currentNode}/>
        <div className="menu" style={{visibility: menuStatus, left: positionX, top: positionY}}>
          <div className="info-menu">
            <span>NodeType<i>{currentNode.NodeType}</i></span>
            <span>String<br></br><i >{currentNode.str}</i></span>
          </div>
        </div>
        <div className="operate-list">
          <span title="zoom out" onClick={this.zoomOut}><Icon type="plus-circle" /></span>
          <span title="zoom in" onClick={this.zoomIn}><Icon type="minus-circle" /></span>
          <span onClick={this.viewFullPage}>
            {isFullScreen ?<Icon type="fullscreen" /> : <Icon type="fullscreen-exit" />}
          </span>
        </div>
      </div>
      </div>
    )
  }
}

export default TreeMap;
