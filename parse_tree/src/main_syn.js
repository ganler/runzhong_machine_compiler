export default {
	name:"程序",
	str:" ",
	NodeType:"N-T",
	children: [
		{
			name:"程序",
			str:" ",
			NodeType:"N-T",
			children: [
				{
					name:"程序",
					str:" ",
					NodeType:"N-T"
				},
				{
					name:"声明",
					str:" ",
					NodeType:"N-T",
					children: [
						{
							name:"函数声明",
							str:" ",
							NodeType:"N-T",
							children: [
								{
									name:"}",
									str:"} ",
									NodeType:"T"
								},
								{
									name:"语句块",
									str:" ",
									NodeType:"N-T",
									children: [
										{
											name:"语句块",
											str:" ",
											NodeType:"N-T",
											children: [
												{
													name:"语句块",
													str:" ",
													NodeType:"N-T",
													children: [
														{
															name:"语句块",
															str:" ",
															NodeType:"N-T"
														},
														{
															name:"赋值语句",
															str:" ",
															NodeType:"N-T",
															children: [
																{
																	name:"表达式",
																	str:" ",
																	NodeType:"N-T",
																	children: [
																		{
																			name:"关系式",
																			str:" ",
																			NodeType:"N-T",
																			children: [
																				{
																					name:";",
																					str:"; ",
																					NodeType:"T"
																				}
																			]
																		},
																		{
																			name:"加减表达式",
																			str:" ",
																			NodeType:"N-T",
																			children: [
																				{
																					name:"加减操作",
																					str:" ",
																					NodeType:"N-T"
																				},
																				{
																					name:"项",
																					str:" ",
																					NodeType:"N-T",
																					children: [
																						{
																							name:"乘除操作",
																							str:" ",
																							NodeType:"N-T"
																						},
																						{
																							name:"因子",
																							str:" ",
																							NodeType:"N-T",
																							children: [
																								{
																									name:"后缀",
																									str:" ",
																									NodeType:"N-T",
																									children: [
																										{
																											name:")",
																											str:") ",
																											NodeType:"T"
																										},
																										{
																											name:"实参列表",
																											str:" ",
																											NodeType:"N-T",
																											children: [
																												{
																													name:"void",
																													str:"void ",
																													NodeType:"T"
																												}
																											]
																										},
																										{
																											name:"(",
																											str:"( ",
																											NodeType:"T"
																										}
																									]
																								},
																								{
																									name:"标识符",
																									str:"zzznb ",
																									NodeType:"T"
																								}
																							]
																						}
																					]
																				}
																			]
																		}
																	]
																},
																{
																	name:"赋值符",
																	str:"= ",
																	NodeType:"T"
																},
																{
																	name:"标识符",
																	str:"txc ",
																	NodeType:"T"
																}
															]
														}
													]
												},
												{
													name:"赋值语句",
													str:" ",
													NodeType:"N-T",
													children: [
														{
															name:"表达式",
															str:" ",
															NodeType:"N-T",
															children: [
																{
																	name:"关系式",
																	str:" ",
																	NodeType:"N-T",
																	children: [
																		{
																			name:";",
																			str:"; ",
																			NodeType:"T"
																		}
																	]
																},
																{
																	name:"加减表达式",
																	str:" ",
																	NodeType:"N-T",
																	children: [
																		{
																			name:"加减操作",
																			str:" ",
																			NodeType:"N-T",
																			children: [
																				{
																					name:"加减操作",
																					str:" ",
																					NodeType:"N-T"
																				},
																				{
																					name:"项",
																					str:" ",
																					NodeType:"N-T",
																					children: [
																						{
																							name:"乘除操作",
																							str:" ",
																							NodeType:"N-T",
																							children: [
																								{
																									name:"乘除操作",
																									str:" ",
																									NodeType:"N-T"
																								},
																								{
																									name:"因子",
																									str:" ",
																									NodeType:"N-T",
																									children: [
																										{
																											name:"数字",
																											str:"3 ",
																											NodeType:"T"
																										}
																									]
																								},
																								{
																									name:"乘除运算符",
																									str:"* ",
																									NodeType:"T"
																								}
																							]
																						},
																						{
																							name:"因子",
																							str:" ",
																							NodeType:"N-T",
																							children: [
																								{
																									name:"数字",
																									str:"1 ",
																									NodeType:"T"
																								}
																							]
																						}
																					]
																				},
																				{
																					name:"加减运算符",
																					str:"+ ",
																					NodeType:"T"
																				}
																			]
																		},
																		{
																			name:"项",
																			str:" ",
																			NodeType:"N-T",
																			children: [
																				{
																					name:"乘除操作",
																					str:" ",
																					NodeType:"N-T"
																				},
																				{
																					name:"因子",
																					str:" ",
																					NodeType:"N-T",
																					children: [
																						{
																							name:"数字",
																							str:"233 ",
																							NodeType:"T"
																						}
																					]
																				}
																			]
																		}
																	]
																}
															]
														},
														{
															name:"赋值符",
															str:"= ",
															NodeType:"T"
														},
														{
															name:"标识符",
															str:"lrz ",
															NodeType:"T"
														}
													]
												}
											]
										},
										{
											name:"内部声明",
											str:" ",
											NodeType:"N-T",
											children: [
												{
													name:"内部声明1",
													str:" ",
													NodeType:"N-T",
													children: [
														{
															name:"内部声明1",
															str:" ",
															NodeType:"N-T",
															children: [
																{
																	name:";",
																	str:"; ",
																	NodeType:"T"
																}
															]
														},
														{
															name:"标识符",
															str:"txc ",
															NodeType:"T"
														},
														{
															name:",",
															str:", ",
															NodeType:"T"
														}
													]
												},
												{
													name:"标识符",
													str:"lrz ",
													NodeType:"T"
												},
												{
													name:"int",
													str:"int ",
													NodeType:"T"
												}
											]
										}
									]
								},
								{
									name:"{",
									str:"{ ",
									NodeType:"T"
								},
								{
									name:")",
									str:") ",
									NodeType:"T"
								},
								{
									name:"形参列表",
									str:" ",
									NodeType:"N-T",
									children: [
										{
											name:"空形参",
											str:" ",
											NodeType:"N-T",
											children: [
												{
													name:"void",
													str:"void ",
													NodeType:"T"
												}
											]
										}
									]
								},
								{
									name:"(",
									str:"( ",
									NodeType:"T"
								}
							]
						},
						{
							name:"标识符",
							str:"main ",
							NodeType:"T"
						},
						{
							name:"void",
							str:"void ",
							NodeType:"T"
						}
					]
				}
			]
		},
		{
			name:"声明",
			str:" ",
			NodeType:"N-T",
			children: [
				{
					name:"声明1",
					str:" ",
					NodeType:"N-T",
					children: [
						{
							name:"函数声明",
							str:" ",
							NodeType:"N-T",
							children: [
								{
									name:"}",
									str:"} ",
									NodeType:"T"
								},
								{
									name:"语句块",
									str:" ",
									NodeType:"N-T",
									children: [
										{
											name:"语句块",
											str:" ",
											NodeType:"N-T"
										},
										{
											name:"return语句",
											str:" ",
											NodeType:"N-T",
											children: [
												{
													name:"返回值",
													str:" ",
													NodeType:"N-T",
													children: [
														{
															name:"表达式",
															str:" ",
															NodeType:"N-T",
															children: [
																{
																	name:"关系式",
																	str:" ",
																	NodeType:"N-T",
																	children: [
																		{
																			name:";",
																			str:"; ",
																			NodeType:"T"
																		}
																	]
																},
																{
																	name:"加减表达式",
																	str:" ",
																	NodeType:"N-T",
																	children: [
																		{
																			name:"加减操作",
																			str:" ",
																			NodeType:"N-T"
																		},
																		{
																			name:"项",
																			str:" ",
																			NodeType:"N-T",
																			children: [
																				{
																					name:"乘除操作",
																					str:" ",
																					NodeType:"N-T"
																				},
																				{
																					name:"因子",
																					str:" ",
																					NodeType:"N-T",
																					children: [
																						{
																							name:"数字",
																							str:"666 ",
																							NodeType:"T"
																						}
																					]
																				}
																			]
																		}
																	]
																}
															]
														}
													]
												},
												{
													name:"return",
													str:"return ",
													NodeType:"T"
												}
											]
										}
									]
								},
								{
									name:"{",
									str:"{ ",
									NodeType:"T"
								},
								{
									name:")",
									str:") ",
									NodeType:"T"
								},
								{
									name:"形参列表",
									str:" ",
									NodeType:"N-T",
									children: [
										{
											name:"空形参",
											str:" ",
											NodeType:"N-T",
											children: [
												{
													name:"void",
													str:"void ",
													NodeType:"T"
												}
											]
										}
									]
								},
								{
									name:"(",
									str:"( ",
									NodeType:"T"
								}
							]
						}
					]
				},
				{
					name:"标识符",
					str:"zzznb ",
					NodeType:"T"
				},
				{
					name:"int",
					str:"int ",
					NodeType:"T"
				}
			]
		}
	]
}