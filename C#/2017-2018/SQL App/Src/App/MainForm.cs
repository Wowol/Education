using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Npgsql;

namespace App
{
    public partial class MainForm : Form
    {
        private TreeNode lastSelectedNode;
        private string selectedColumnName;

        private const int CONDITIONAL_PANELS_GAP = 10;

        bool lastIsView = false;

        Panel lastPanel;
        DataTable lastTable;
        string lastTableName;

        List<Conditional> conditionals = new List<Conditional>();

        public MainForm()
        {
            InitializeComponent();
            Dbo.ConnectToDatabase();
            Dbo.Execute("SET SCHEMA 'ksiegarnia_internetowa'");
            AddTablesToComboBox();

            lastPanel = firstPanel;
        }

        public void AddTablesToComboBox()
        {
            foreach (DataRow table in Dbo.GetTablesFromSchema().Rows)
            {
                TreeNode node = new TreeNode(table.ItemArray[0].ToString());

                foreach (DataColumn column in Dbo.GetWholeTable(table.ItemArray[0].ToString()).Columns)
                {
                    node.Nodes.Add(column.ColumnName);
                }

                tablesTreeView.Nodes.Add(node);
            }
        }

        private string GetSelectedTableName()
        {
            return tablesTreeView.SelectedNode.Parent == null ? tablesTreeView.SelectedNode.Text : tablesTreeView.Parent.Text;
        }

        private void SetEditable(bool editable)
        {
            grid.AllowUserToDeleteRows = true;
            grid.AllowDrop = grid.AllowUserToAddRows = editable;
        }


        private void ShowTable(string table)
        {
            grid.DataSource = Dbo.GetWholeTable(table);
            lastTableName = table;
        }

        private void CreateNewConditionalPanel()
        {
            Panel newPanel = new Panel();
            conditionalPanel.Controls.Add(newPanel);
            newPanel.Size = lastPanel.Size;
            newPanel.Location = new Point(lastPanel.Location.X, lastPanel.Location.Y + CONDITIONAL_PANELS_GAP + lastPanel.Size.Height);

            newPanel.Controls.Add(CreateNewNameTextBoxInConditionalPanel());
            newPanel.Controls.Add(CreateNewComboBoxInConditionalPanel());
            newPanel.Controls.Add(CreateNewValueTextBoxInConditionalPanel());

            lastPanel = newPanel;

            conditionalPanel.Controls.Add(newPanel);
        }

        private TextBox CreateNewNameTextBoxInConditionalPanel()
        {
            return new TextBox
            {
                Size = lastPanel.Controls[0].Size,
                Location = lastPanel.Controls[0].Location,
                TabIndex = lastPanel.Controls[0].TabIndex + 3
            };
        }

        private ComboBox CreateNewComboBoxInConditionalPanel()
        {
            ComboBox c = new ComboBox
            {
                Size = lastPanel.Controls[1].Size,
                Location = lastPanel.Controls[1].Location,
                TabIndex = lastPanel.Controls[1].TabIndex + 3

            };
            foreach (String o in ((ComboBox)lastPanel.Controls[1]).Items)
            {
                c.Items.Add(o);
            }
            return c;
        }

        private TextBox CreateNewValueTextBoxInConditionalPanel()
        {
            TextBox d = new TextBox
            {
                Size = lastPanel.Controls[2].Size,
                Location = lastPanel.Controls[2].Location,
                TabIndex = lastPanel.Controls[2].TabIndex + 3
            };

            d.KeyDown += new KeyEventHandler(valueTextBox_KeyDown);
            return d;
        }



        private void ShowNodeTable()
        {
            if (lastIsView)
            {
                lastTable = Dbo.GetTable(lastTableName, GetAllConditionals());
                grid.DataSource = lastTable;
            }
            else if (lastSelectedNode.Parent == null)
            {
                lastTableName = lastSelectedNode.Text;
                lastTable = Dbo.GetTable(lastSelectedNode.Text, GetAllConditionals());
                grid.DataSource = lastTable;
                SetEditable(false);
            }
            else
            {
                lastTableName = lastSelectedNode.Parent.Text;
                lastTable = Dbo.GetTable(lastSelectedNode.Parent.Text, GetAllConditionals());
                grid.DataSource = Dbo.GetTable(lastSelectedNode.Parent.Text, GetAllConditionals(), lastSelectedNode.Text);
                SetEditable(false);
            }
            ShowAddNewRow(lastTable);
        }

        private void ShowAddNewRow(DataTable data)
        {
            addNewPanel.Controls.Clear();
            int textBoxWidth = 100;
            int textBoxGap = 10;
            int i = 0;
            foreach (DataColumn column in data.Columns)
            {
                TextBox valueTextBox = new TextBox();
                valueTextBox.Width = textBoxWidth;
                int xLocation = i++ * (textBoxGap + textBoxWidth) + textBoxGap;
                valueTextBox.Location = new Point(xLocation, 20);
                valueTextBox.Name = column.ColumnName;

                Label columnNameLabel = new Label();
                columnNameLabel.Text = column.ColumnName;
                columnNameLabel.Location = new Point(xLocation, 0);

                addNewPanel.Controls.Add(columnNameLabel);
                addNewPanel.Controls.Add(valueTextBox);

            }
        }

        private void ClearConditionals()
        {
            for (int x=1; x<conditionalPanel.Controls.Count; x++)
            {
                conditionalPanel.Controls.RemoveAt(x);
                x--;
            }
            lastPanel = firstPanel;
            firstPanel.GetColumnTextBox().Text = String.Empty;
            firstPanel.GetOperatorComboBox().Text = String.Empty;
            firstPanel.GetValueTextBox().Text = String.Empty;
        }



        #region Events


        private void grid_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            MessageBox.Show(e.Exception.Message);
        }

        private void TablesTreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            lastIsView = false;
            lastSelectedNode = e.Node;
            ClearConditionals();
            ClearSqlRichTextBox();
            ShowNodeTable();
        }

        private void ClearSqlRichTextBox()
        {
            sqlTextBox.Clear();
        }


        private void grid_ColumnHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                selectedColumnName = grid.Columns[e.ColumnIndex].Name;
                lastPanel.GetColumnTextBox().Text = selectedColumnName;
            }
        }

        private void valueTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                TextBox t = (TextBox) sender;
                Panel parentPanel = (Panel)t.Parent;
                string columnName = parentPanel.Controls[0].Text;
                string op = parentPanel.Controls[1].Text;
                string value = parentPanel.Controls[2].Text;

                try
                {
                    ShowNodeTable();
                    if (!String.IsNullOrWhiteSpace(lastPanel.GetColumnTextBox().Text))
                        CreateNewConditionalPanel();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }


        #endregion

        private List<Conditional> GetAllConditionals()
        {
            List<Conditional> result = new List<Conditional>();
            foreach(Panel p in conditionalPanel.Controls)
            {
                string columnName = p.GetColumnTextBox().Text;
                string op = p.GetOperatorComboBox().Text;
                string value = p.GetValueTextBox().Text;

                if (String.IsNullOrWhiteSpace(op) || String.IsNullOrWhiteSpace(columnName))
                {
                    continue;
                }

                result.Add(new Conditional(columnName, op, value));
            }
            return result;
        }

        private void sqlButtonRun_Click(object sender, EventArgs e)
        {
            try
            {
                grid.DataSource = Dbo.GetTable(sqlTextBox.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void grid_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                int rowIndex = grid.SelectedCells[0].RowIndex;
                int columnIndex = grid.SelectedCells[0].ColumnIndex;
                if (columnIndex == grid.ColumnCount - 1)
                {
                    MessageBox.Show(rowIndex.ToString());
                }
            }

        }

        private void addNewButton_Click(object sender, EventArgs e)
        {
            List<String> columnValues = new List<String>();
            foreach(Control c in addNewPanel.Controls)
            {
                if (c is TextBox)
                {
                    TextBox textBox = (TextBox) c;
                    columnValues.Add(!String.IsNullOrWhiteSpace(textBox.Text) ? textBox.Text : "NULL");
                }
            }
            try
            {
                Dbo.InsertValues(lastTableName, columnValues.ToArray());
                ShowTable(lastTableName);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void grid_RowsRemoved(object sender, DataGridViewRowsRemovedEventArgs e)
        {
        }

        private void grid_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            e.Cancel = true;
            List<Conditional> conditionals = new List<Conditional>();
            int currentColumn = 0;
            foreach (DataGridViewCell cell in e.Row.Cells)
            {
                string columnName = grid.Columns[currentColumn++].Name;
                string value = cell.Value.ToString();
                if (String.IsNullOrEmpty(value))
                {
                    conditionals.Add(new Conditional(columnName, "IS NULL", string.Empty));
                    continue;
                }
                else if (cell.ValueType.ToString() == "System.String" || cell.ValueType.ToString() == "System.DateTime")
                {
                    value = "\'" + value + "\'";
                }
                conditionals.Add(new Conditional(columnName, "=", value));

            }
            try
            {
                Dbo.DeleteValues(lastTableName, conditionals);
                ShowTable(lastTableName);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SelectedView();
            Dbo.Execute(SqlQueryConsts.BOOKS_QUERY);
            ShowTable("books_query");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SelectedView();
            Dbo.Execute(SqlQueryConsts.BOOKS_STATS);
            ShowTable("books_stats");
        }

        private void SelectedView()
        {
            ClearConditionals();
            ClearSqlRichTextBox();
            lastIsView = true;
            grid.AllowUserToDeleteRows = false;
            grid.AllowUserToAddRows = false;
        }

        private void miasta_stats_Click(object sender, EventArgs e)
        {
            SelectedView();
            Dbo.Execute(SqlQueryConsts.CITY_STATS);
            ShowTable("city_stats");
        }

        private void wydawnictwaStats_Click(object sender, EventArgs e)
        {
            SelectedView();
            Dbo.Execute(SqlQueryConsts.WYD_STATS);
            ShowTable("wyd_stats");
        }

        private void similarBookTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                string title = "\'" + similarBookTextBox.Text + "\'";
                try
                {
                    grid.DataSource = Dbo.GetTable(String.Format("SELECT * from find_similar(" + title + ")"));
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SelectedView();
            Dbo.Execute(SqlQueryConsts.ZAM_STATS);
            ShowTable("zamowienia_koszty");
        }
    }
}

