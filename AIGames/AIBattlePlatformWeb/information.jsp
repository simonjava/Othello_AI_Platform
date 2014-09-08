<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@page import="com.platform.operator.InformationOperator"%>
<%@page import="com.platform.entity.Information"%>
<%@page import="com.platform.entity.Task"%>
<%@page import="com.platform.operator.TaskOperator"%>
<%@page import="com.platform.operator.ReplayOperator"%>
<%@page import="com.platform.entity.Replay"%>

<%
	String id = (String) session.getAttribute("id");
	List<Information> inforList = InformationOperator
			.getInformationById(id);
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
	<head>
		<title>AI对战平台-个人信息</title>
		<link rel="stylesheet" type="text/css" href="css/styles.css"
			media="screen" />
		<link rel="stylesheet" type="text/css" href="css/print.css"
			media="print" />
		<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>

	</head>

	<body>
		<div id="wrapper">


			<a href="main.jsp"> <header> <!-- header --> </header> </a>
			<!-- end of header -->

			<!-- start of top nav -->
			<%@include file="Nav.txt"%>
			<!-- end of top nav -->
			<section id="main2">
			<article>
			<div style="text-align: center; width: 930px;">
				<table style="text-align: left; margin: auto;font-size: 20px;">
					<caption>
						用户:<%=id%></caption>
					<thead>
						<tr>
							<th>
								游戏类别
							</th>
							<th>
								比赛次数
							</th>
							<th>
								胜利次数
							</th>
							<th>
								得分
							</th>
						</tr>
					</thead>
					<tbody>
						<%
							for (Iterator<Information> i = inforList.listIterator(); i
									.hasNext();)
							{
								Information infor = (Information) i.next();
						%>

						<tr>
							<td>
								:
								<%=infor.getGame()%></td>
							<td>
								得分:
								<%=infor.getScore()%></td>

							<td>
								比赛次数:
								<%=infor.getContest_times()%></td>
							<td>
								胜利次数:
								<%=infor.getWin()%></td>
						</tr>
					</tbody>
				</table>



			</div>
			<%
				}
			%> </article>
			</section>
			<!-- end of #main content and sidebar-->
			<%@ include file="Foot"%>
			<!-- #wrapper -->
			<!-- Free template created by http://bestmoban.com -->
	</body>
</html>
<%@ include file="fuckIE"%>