import java.io.*;

public class binfa {

    static class BinfaNode {
        private char data;
        private BinfaNode left_child_charptr, right_child_charptr;

        public BinfaNode(char init_char) {
            data = init_char;
            left_child_charptr = right_child_charptr = null;
        }

        public BinfaNode() {
            data = '/';
            left_child_charptr = right_child_charptr = null;
        }


        char get_data() {
            return data;
        }

        BinfaNode get_left_child() {
            return left_child_charptr;
        }

        BinfaNode get_right_child() {
            return right_child_charptr;
        }

        void set_left_child(BinfaNode node) {
            left_child_charptr = node;
        }

        void set_right_child(BinfaNode node) {
            right_child_charptr = node;
        }

        boolean HasChild() {
            return (right_child_charptr != null) || (left_child_charptr != null);
        }

    };
	static class binfa_class {
		public binfa_class() {
			root = new BinfaNode();
			traverse_depth = 0;
			insertion_depth = 0;
			mean_sum = 0;
			external_nodes = 1;
			current_node = root;
			max_depth = 0;
		}

		double Mean() {
			return (double) mean_sum / external_nodes;
		}

		double Variance() {

			double var = 0.0;
			variance_sum = 0;

			rvar(root);

			if ((external_nodes - 1) > 0)
				var = StrictMath.sqrt(variance_sum / (external_nodes - 1));
			else
				var = StrictMath.sqrt(variance_sum);

			return var;

		}

		void rvar(BinfaNode node) {
			double avg = Mean();

			if (node != null) {
				++traverse_depth;
				rvar(node.get_right_child());
				rvar(node.get_left_child());
				--traverse_depth;
				if (!node.HasChild())
					variance_sum += ((traverse_depth - avg) * (traverse_depth - avg));

			}

		}

		BinfaNode get_root_node() {
			return root;
		}

		void Print(BinfaNode node, PrintWriter wr) {

			if (node != null) {
				++traverse_depth;
				Print(node.get_left_child(), wr);
				for (int i = 0; i < traverse_depth; ++i)
					wr.print("-");
				wr.println(node.get_data() + "(" + (traverse_depth - 1) + ")");

				Print(node.get_right_child(), wr);
				--traverse_depth;

			}

		}

		int get_max_depth() {
			return max_depth;
		}

		/*int get_external_nodes() {
			return external_nodes;
		}*/

		public void addChar(char c_char) {
			BinfaNode temp_node;

			if (c_char == '0') {
				temp_node = current_node.get_left_child();
			} else {
				temp_node = current_node.get_right_child();
			}
			++insertion_depth;

			if (temp_node != null) {
				current_node = temp_node;
			} else {
				BinfaNode new_node = new BinfaNode(c_char);

				if (current_node.HasChild()) {
					external_nodes++;
					mean_sum += insertion_depth;
				} else
					++mean_sum;

				if (c_char == '0')
					current_node.set_left_child(new_node);
				else
					current_node.set_right_child(new_node);

				if (insertion_depth > max_depth)
					max_depth = insertion_depth;

				insertion_depth = 0;

				current_node = root;
			}
		}

		BinfaNode root = new BinfaNode();
		BinfaNode current_node;

		int insertion_depth;
		int traverse_depth;
		int max_depth;
		int mean_sum;
		double variance_sum;
		int external_nodes;

	};









public static void main(String[] args) {

			try {
				if (args.length != 2) {
					System.err.println("Hibás argumentumszám");
					System.exit(-1);
				}

				FileReader inputStream = new FileReader(args[0]);

				int j;
				boolean inComment = false;
				char i;
				binfa_class bt = new binfa_class();

				while ((j = inputStream.read()) != -1) {

					i = (char) j;

					if (i == '>') {
						inComment = true;
						continue;
					}

					if (i == '\n') {
						inComment = false;
						continue;
					}

					if (inComment)
						continue;

					if (i == 'N')
						continue;

					for (int k = 0; k < 8; k++) {

						if ((i & 0x80) == 0x80)
							bt.addChar('1');
						else
							bt.addChar('0');

						i <<= 1;
					}

				}

				inputStream.close();
				PrintWriter pw = new PrintWriter(new FileWriter(args[1]));

				bt.Print(bt.get_root_node(), pw);
				pw.println("Mélység: " + bt.get_max_depth());
				pw.println("Átlag: " + bt.Mean());
				pw.println("Szórás: " + bt.Variance());

				pw.close();

			} catch (IOException e) {
			}
    }
};
