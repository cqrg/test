using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;




namespace WindowsFormsApplication3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
        }
        // 用于存储当前操作的文件的名称
        private string textFileName = "";
       // private string filePath = "";
        private void Form1_Load(object sender, EventArgs e)
        {
       
       
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            textFileName = "";
            // 新建一个文本时，若输入框中的内容不为空，应先提示“是否保存”
            if (TextBox1.Text != string.Empty)
            {
                if (MessageBox.Show("是否保存当前文件？", "倩女温馨提示", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Information)
                    == DialogResult.Yes)
                {
                    Save();
                 //   Application.Exit();
                }
            }
            //else
            //{
            //    Application.Exit();
            //}
            
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void 保存ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void 关于记事本ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("\n倩女记事本，不一样的记事本~(≧▽≦)/~\n\n\t\t\tBy 刘倩", "关于");
        }

        private void toolStripContainer2_BottomToolStripPanel_Click(object sender, EventArgs e)
        {

        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

        }



        private void 关于AToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 打开ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            openFile.Filter = "文本文档(*.txt)|*.txt|RTF文件(*.rtf)|*.rtf|所有文件|*.*";
            openFile.RestoreDirectory = true;
            openFile.FilterIndex = 1;
            if (openFile.ShowDialog() == DialogResult.OK)
            {
                StreamReader sr = new StreamReader(openFile.FileName);
                TextBox1.Text = sr.ReadToEnd().ToString();
                sr.Close();
                FileInfo fileInfo = new FileInfo(openFile.FileName);// 把标题改为打开的文件的名称
                Text = "*" + fileInfo.Name + "倩女记事本";
                textFileName = fileInfo.Name;
                sr.Dispose();
            }
        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void 新建NToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textFileName = "";
            // 新建一个文本时，若输入框中的内容不为空，应先提示“是否保存”
            if (TextBox1.Text != string.Empty)
            {
                // 若用户选择“是”，应弹出保存文件的对话框
                if (MessageBox.Show("是否保存当前文件？", "倩女温馨提示", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Information)
                    == DialogResult.Yes)
                {
                    // 保存文件
                    Save();
                    Text = "新建-倩女记事本";
                    TextBox1.Text = "";
                }
                else
                {
                    // 用户选择不保存时将输入框中的内容清除
                    TextBox1.Text = "";
            
                }
            }
        }

        private void Save()
        {
                // 默认保存格式
                SaveFileDialog saveFile = new SaveFileDialog();
                saveFile.DefaultExt = "*.txt";
                saveFile.Filter = "文本文档(*.txt)|*.txt|所有文件|*.*";
                if (saveFile.ShowDialog() == DialogResult.OK)
                {
                    StreamWriter sw = new StreamWriter(saveFile.FileName, false);
                    sw.WriteLine(TextBox1.Text);
                    sw.Dispose();
                    MessageBox.Show("文件保存成功！", "提示");
                }
            
        }


        private void 另存为ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog();
            saveFile.DefaultExt = "*.txt";
            saveFile.Filter = "文本文档(*.txt)|*.txt|RTF文件(*.rtf)|*.rtf|所有文件|*.*";
            if(saveFile.ShowDialog()== DialogResult.OK)
            {
                StreamWriter sw = File.AppendText(saveFile.FileName);
                sw.WriteLine(TextBox1.Text);
                sw.Dispose();
            }
            new System.Windows.Forms.ToolStripSeparator();
        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // 退出时应提示用户是否保存当前文本文件
            if (MessageBox.Show("是否将更改保存？", "倩女温馨提示", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Information) == DialogResult.Yes)
            {
                Save();
                Application.Exit();
            }
            else
            {
                Application.Exit();
            }

        }

        private string selectedInfo = "";
        private void 编辑EToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ((TextBox1.SelectedText.Equals("")) && (selectedInfo.Equals("")))
            {
                剪切ToolStripMenuItem.Enabled = false;
                复制ToolStripMenuItem.Enabled = false;
                粘贴ToolStripMenuItem.Enabled = false;
                删除ToolStripMenuItem.Enabled = false;
            }
            else
            {
                剪切ToolStripMenuItem.Enabled = true;
                复制ToolStripMenuItem.Enabled = true;
                粘贴ToolStripMenuItem.Enabled = true;
                删除ToolStripMenuItem.Enabled = true;
            }
        }
        private void 撤销ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextBox1.Undo();
        }
        private void 剪切ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            selectedInfo = TextBox1.SelectedText;
            TextBox1.Cut();  //纯文本格式剪切
            //Clipboard.SetDataObject(selectedInfo);
            //TextBox1.Text = TextBox1.Text.Remove(TextBox1.SelectionStart, TextBox1.SelectionLength);
            //TextBox1.Select(TextBox1.Text.Length, 0);
        }



        private void 复制ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            selectedInfo = TextBox1.SelectedText;
            TextBox1.Copy();
            //Clipboard.SetText(selectedInfo);
        }

        private void 粘贴ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextBox1.Paste();
            //TextBox1.Text += Clipboard.GetText(); 
            //TextBox1.Select(TextBox1.Text.Length, 0); 
        }

        private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //TextBox1.Text = TextBox1.Text.Remove(TextBox1.Text.Length - TextBox1.SelectedText.Length, TextBox1.SelectedText.Length);
            //TextBox1.Select(TextBox1.Text.Length, 0);
            TextBox1.SelectedText = "";

        }

        private void 查找ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (TextBox1.Text == string.Empty)
            {
                MessageBox.Show("请确保要查找的文件的内容不为空！", "倩女温馨提示");
            }
        }

        private void 查找下一个ToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void 替换ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 转到ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 全选ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextBox1.SelectAll();
        }

        private void 时间日期ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextBox1.AppendText(System.DateTime.Now.ToString()+"\n");

        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {

        }


        private void 字体ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FontDialog fontDialog = new FontDialog();
            fontDialog.ShowColor = true;
            if (fontDialog.ShowDialog() == DialogResult.OK)
            {
                TextBox1.SelectionFont = fontDialog.Font;
                TextBox1.SelectionColor = fontDialog.Color;
            }
        }

        private void 自动换行ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (自动换行ToolStripMenuItem.Checked == false)
            {
                TextBox1.WordWrap = true;
                自动换行ToolStripMenuItem.Checked = true;
            }
            else
            {
                TextBox1.WordWrap = false;
                自动换行ToolStripMenuItem.Checked = false; ;
            }
        }


        private void 查看VToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (TextBox1.Text.Length > 0)
            {
                statusStrip1.Enabled = true;
            }
            else
            {
                statusStrip1.Enabled = false;
            }
        }

       //private void 工具栏TToolStripMenuItem_Click(object sender, EventArgs e)
       // {
       //     Point point;
       //     int sideH;
       //     if (工具栏TToolStripMenuItem.Checked == true)
       //     {
       //         //隐藏工具栏时，把坐标设为（0，28）,因为菜单的高度为28
       //        point = new Point(0, 工具栏TToolStripMenuItem.Height);
       //         工具栏TToolStripMenuItem.Checked = false;
       //         toolStrip1.Visible = false;
       //        TextBox1.Location = point;
       //        TextBox1.Height += 工具栏TToolStripMenuItem.Height;
       //     }
       //     else
       //     {
       //         sideH = menuStrip1.Height + 工具栏TToolStripMenuItem.Height;
       //         point = new Point(0, sideH);
       //         工具栏TToolStripMenuItem.Checked = true;
       //         toolStrip1.Visible = true;
       //         TextBox1.Location = point;
       //         TextBox1.Height -= 工具栏TToolStripMenuItem.Height;
       //     }
       // }

        private void 状态栏ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (状态栏ToolStripMenuItem.Checked == true)
            {
                状态栏ToolStripMenuItem.Checked = false;
                statusStrip1.Visible = false;
                TextBox1.Height += 状态栏ToolStripMenuItem.Height;
            }
            else
            {
                状态栏ToolStripMenuItem.Checked = true;
                statusStrip1.Visible = true;
                TextBox1.Height -= 状态栏ToolStripMenuItem.Height;

            }
        }
        private void TextBox1_TextChanged(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "当前计数" + this.TextBox1.Text.Length.ToString();
            //toolStripStatusLabel2.Text = DateTime.Now.ToString();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabel2.Text = System.DateTime.Now.ToString();
        }

        private void TextBox1_TextChanged_1(object sender, EventArgs e)
        {

        }
    }
}