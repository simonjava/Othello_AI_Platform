<%@page import="com.platform.common.Constant"%>
<%@page import="com.csm.web.pageUtil.PageModel"%>
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<%@taglib uri="http://javacrazyer.iteye.com/tags/pager" prefix="w"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<%@page import="com.platform.operator.InformationOperator"%>
<%@page import="com.platform.entity.Information"%>
<%@page import="com.platform.entity.Task"%>
<%@page import="com.platform.operator.TaskOperator"%>
<%@page import="com.platform.operator.ReplayOperator"%>
<%@page import="com.platform.entity.Replay"%>

<%
	PageModel<Replay> pm = (PageModel<Replay>) request
			.getAttribute("pm");
	if (pm == null)
	{
		response.sendRedirect("GetReplayServlet");
	}
	List<Replay> replayList = pm.getDatas();
	String id = (String) session.getAttribute("id");
	List<Information> inforList = InformationOperator
			.getInformationById(id);
	List<Information> top10List = InformationOperator
			.getRankTop10("othello");
	List<Task> taskList = TaskOperator.getTasksById(id);
	List<Task> pkTask = TaskOperator.getCorrectTask("othello");
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<title>AI对战平台-<%=id%></title>
<link rel="stylesheet" type="text/css" href="css/styles.css"
	media="screen" />
<link rel="stylesheet" type="text/css" href="css/print.css"
	media="print" />
<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>

</head>

<body>
	<div id="wrapper">

		<!-- #wrapper -->

		<a href="main.jsp"> <header> <!-- header --> </header> </a>
		<!-- end of header -->

		<!-- start of top nav -->
		<%@include file="Nav.txt"%>
		<!-- end of top nav -->

		<section id="main"> <!-- #main content and sidebar area -->
		<section id="content"> <!-- #content --> <article>
		<h2></h2>
		<table>
			<caption style="font-size: 30px;text-align: left;color: #000000">代码状态</caption>
			<thead>
				<tr>
					<th>用户</th>
					<th>游戏</th>
					<th>编译状态</th>
					<th>编译环境</th>
					<th>提交时间</th>
					<th>查看代码</th>
					<th>操作</th>
				</tr>
			</thead>
			<tbody>
				<%
					if (taskList.size() < 1)
					{
				%>
				<tr>
					<td colspan="5">你还没有一份能拿来比赛的代码，赶快 <a href="submitCode.jsp"
						target="_blank">点我提交<a />吧 
					</td>
				</tr>
				<%
					}
				%>
				<%
					for (Iterator<Task> i = taskList.listIterator(); i.hasNext();)
					{
						Task task = (Task) i.next();
				%>
				<tr>
					<td><%=task.getUser_id()%></td>
					<td><%=task.getGame()%></td>

					<%
						if ("compile wrong".equals(task.getStatus()))
							{
					%><td style="background: red;"><%=task.getStatus()%><a
						href="msg.jsp?user_id=<%=task.getUser_id()%>&game=<%=task.getGame()%>" target="_blank">查看</a>
					</td>
					<%
						} else if ("compile correct".equals(task.getStatus()))
							{
					%>
					<td style="background: green; color: white;"><%=task.getStatus()%></td>
					<%
						} else
							{
					%>
					<td><%=task.getStatus()%></td>
					<%
						}
					%>

					<td><%=task.getCompile_environment()%></td>
					<td><%=task.getTime()%></td>
					<td><a href="code.jsp?user_id=<%=task.getUser_id()%>&game=<%=task.getGame()%>" target="_blank">查看代码</a></td>
					<td>
						<%
							if ("compile correct".equals(task.getStatus()))
								{
						%> <a href="AddReplayServlet?game=<%=task.getGame()%>">随机对抗</a> <%
 	} else
 		{
 %> 不能比赛 <%
 	}
 %>
					</td>
				</tr>
				<%
					}
				%>
			</tbody>
		</table>
		</article>
		<hr />
		<article>
		<table class="dataTable">
			<caption style="font-size: 30px;text-align: left;color: #000000">
				<a name="replay"></a>比赛回放
			</caption>
			<thead>
				<tr>
					<th>游戏</th>
					<th>用户</th>
					<th>对手</th>
					<th>比赛时间</th>
					<th>比赛状态</th>
					<th>赢家</th>
					<th>操作</th>
				</tr>
			</thead>
			<%
				if (replayList.size() < 1)
				{
			%>
			<tr>
				<td colspan="6">你还没有参加过任何比赛！先做一个强力AI吧~</td>
			</tr>
			<%
				}
			%>
			<%
				for (int i = 0; i < replayList.size(); i++)
				{
					Replay re = (Replay) replayList.get(i);
			%>
			<tr <%if (i % 2 == 0)
				{%> class="odd" <%}%>>
				<td><%=re.getGame()%></td>
				<%
					if (id.equals(re.getPlayer1()))
						{
				%>
				<td style="background: #000000; color: #ffffff"><%=re.getPlayer1()%></td>
				<%
					} else
						{
				%>
				<td><%=re.getPlayer1()%></td>
				<%
					}
				%>
				<%
					if (id.equals(re.getPlayer2()))
						{
				%>
				<td style="background: #000000; color: #ffffff"><%=re.getPlayer2()%></td>
				<%
					} else
						{
				%>
				<td><%=re.getPlayer2()%></td>
				<%
					}
				%>

				<td><%=re.getTime()%></td>
				<%
					if ("contest over".equals(re.getStatus()))
						{
				%>
				<td style="background: green; color: white;"><%=re.getStatus()%></td>
				<%
					} else
						{
				%>
				<td style="background: red;"><%=re.getStatus()%></td>
				<%
					}
				%>

				<%
					if (re.getWinner() == 1)
						{
				%>
				<%
					if (id.equals(re.getPlayer1()))
							{
				%>
				<td style="background: #ff0000; color: #ffffff"><%=re.getPlayer1()%></td>
				<%
					} else
							{
				%>
				<td><%=re.getPlayer1()%></td>
				<%
					}
				%>
				<%
					} else if (re.getWinner() == 2)
						{
				%>
				<%
					if (id.equals(re.getPlayer2()))
							{
				%>
				<td style="background: #ff0000; color: #ffffff"><%=re.getPlayer2()%></td>
				<%
					} else
							{
				%>
				<td><%=re.getPlayer2()%></td>
				<%
					}
				%>
				<%
					} else
						{
				%>
				<td>Draw</td>
				<%
					}
				%>

				<td><a href="replay.jsp?replay_id=<%=re.getId()%>"
					target="_blank">观看录像</a></td>
			</tr>
			<%
				}
			%>
		</table>
		<w:pager pageSize="${pageSize}" pageNo="${pageNo}"
			url="GetReplayServlet" recordCount="${pm.recordCount }" /> </article> </section> <!-- end of #content -->
		<aside id="sidebar"> <!-- sidebar -->

		<h3>Rank Top 10</h3>
		<ul>
			<%
				for (Iterator<Information> i = top10List.listIterator(); i
						.hasNext();)
				{
					Information infor = (Information) i.next();
			%>
			<li>
				<div class="wrap" width="300px" style="padding-bottom: 30px;">
					<div style="width: 100px;"><%=infor.getUser_id()%></div>
					<div style="width: 50px;"><%=infor.getScore()%></div>
					<div>
						<%
							if (!infor.getUser_id().equalsIgnoreCase(id))
								{
						%><a
							href="AddReplayServlet?player2=<%=infor.getUser_id()%>&game=<%=infor.getGame()%>">挑战</a>
						<%
							}
						%>
					</div>
				</div>
				<div style="clear: both"></div></li>
			<%
				}
			%>


		</ul>



		</aside> <!-- end of sidebar --> </section>
		<!-- end of #main content and sidebar-->

		<%@include file="Foot"%>

	</div>
	<!-- #wrapper -->
	<!-- Free template created by http://bestmoban.com -->
</body>
</html>
<%@ include file="fuckIE"%>
