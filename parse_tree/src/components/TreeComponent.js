/**
 * @author Fine
 * @description d3 and react tree component
 */
import React from 'react';
import * as d3 from 'd3';

import CONSTANT from '../utils/CONSTANT';
import minusCircle from '../assets/circle.svg';
import '../App.css';

class TreeComponent extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      nodes: [], // tree nodes
      links: [], // tree path
    };
    this.tree = null;

    this.bezierCurveGenerator = d3.linkHorizontal()
    .x(d => d.y)
    .y(d => d.x)
  }

  componentDidMount() {
    this.initMapData();
  }

  shouldComponentUpdate(nextProps, nextState) {
    const {links, nodes} = this.initTreeNodes(nextProps);
    nextState.nodes = nodes;
    nextState.links = links;

    return true;
  }

  initMapData() {
    const {width, height, data} = this.props;
    const layerInfos = require('../layer.json');
    // create tree layout
    this.tree = d3.tree()
      .size([width * (layerInfos.layer)/5, height * (layerInfos.layer)/5])
      .separation((a, b) => (a.parent === b.parent ? 5 : 9) / a.depth);
    const {links, nodes} = this.initTreeNodes(data);
    this.setState({links, nodes});
  }

  initTreeNodes(nextProps) {
    const { currentNode, dataSource } = nextProps;
    let nodes = [];
    let links = [];
    if (dataSource) {
      // create data of tree structure
      const hierarchyData = d3.hierarchy(dataSource)
      // hierarchy layout and add node.x,node.y
      const treeNode = this.tree(hierarchyData);
      nodes = treeNode.descendants();
      links = treeNode.links();
      nodes = nodes.map(node => {
        if (node.active) {
          node.active = false;
          //**Active parent node**
          //if (node.parent) {
          //  node.parent.active = false;
          //}
        }
        if (node.data.name === currentNode.name) {
          node.active = true;
          //**Active parent node**
          //if (node.parent) {
          //  node.parent.active = true;
          //}
        }
        return node;
      });
    }
    return {nodes, links};
  }

  nodeActive = (event, currentNode) => {
    // let { nodes } = this.state
    this.props.nodeClick(event, currentNode);
  }

  rectWidth(name) {
    console.log("node_name: "+name+" length: "+name.length);
    return (name.length*15);
  }

  rectX(name) {
    var x=0;
    x = 0-(name.length-1)*6;
    return x;
  }

  textX(name) {
    var x=0;
    x = 0-(name.length-1)*6;
    return x+2;
  }

  render() {
    const { width, height, tranInfo } = this.props;
    const { links, nodes } = this.state;

    return (
      <svg width="3000" height="3000">
        <g
          className="tree_map"
          transform={`translate(${tranInfo.x},${tranInfo.y}),scale(${tranInfo.k})`}>
          <g>
            {
              links.map((link, i) => {
              const start = { x: link.source.x, y: link.source.y + CONSTANT.STARTBUF };
              const end = { x: link.target.x, y: link.target.y + CONSTANT.ENDBUF };
              const pathLink = this.bezierCurveGenerator({ source: start, target: end });

              return <path 
                key={i}
                d={pathLink}
                fill='none'
                stroke={CONSTANT.THEME.LINESTROKE}
                strokeWidth='1'
                strokeDasharray={CONSTANT.THEME.DASHARRAY}
                markerEnd='url(#arrow)'/>
            })}
          </g>
          <g>
            {nodes.map((node, i) => {
              node.str = node.data.str;
              node.NodeType = node.data.NodeType;
              node.name = node.data.name;

              return (<g key={i} transform={`translate(${node.y}, ${node.x - 10})`}>
                <defs>
                  <marker id="arrow"
                    markerUnits="strokeWidth"
                    markerWidth={CONSTANT.MARKER.MARKERWIDTH}
                    markerHeight={CONSTANT.MARKER.MARKERHIEGHT}
                    viewBox={CONSTANT.MARKER.VIEWBOX} 
                    refX={CONSTANT.MARKER.REFX}
                    refY={CONSTANT.MARKER.REFY}
                    orient={CONSTANT.MARKER.ORIENT}>
                    <path d={CONSTANT.MARKER.PATH} fill={CONSTANT.MARKER.FILL} />
                  </marker>
                </defs>
                <circle
                  cx={CONSTANT.CIRCLE.CX}
                  cy={CONSTANT.CIRCLE.CY}
                  r={CONSTANT.CIRCLE.R}
                  fill={CONSTANT.CIRCLE.FILL}
                  stroke={node.active ? CONSTANT.THEME.ACTIVE : CONSTANT.THEME.NONEACTIVE}
                  strokeWidth={node.active ? CONSTANT.CIRCLE.STROKEACTWID : CONSTANT.CIRCLE.STROKENONACTWID}
                  style={{cursor: 'pointer'}}
                  onClick={(event) => this.nodeActive(event, node)} />
                <image
                  href={minusCircle}
                  style={{cursor: 'pointer'}} 
                  onClick={(event) => this.nodeActive(event, node)}/>
                <rect x={this.rectX(node.name)} y='32' width={this.rectWidth(node.name)} height='20'
                  fill={CONSTANT.THEME.RECTBG} />
                <text
                  x={this.textX(node.name)} y='48'
                  fill={CONSTANT.THEME.TEXTCOLOR}
                  className = 'text'
                  >
                  {node.name}
                </text>
              </g>)
            })}
          </g>
        </g>
      </svg>
    )
  }
}

export default TreeComponent;
